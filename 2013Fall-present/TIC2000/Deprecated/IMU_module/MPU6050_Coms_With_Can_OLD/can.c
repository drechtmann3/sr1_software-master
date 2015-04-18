/*//###########################################################################
// Description:
//
// CAN receiver and sender functions
//
// Improvements:
// Handle data with different number of bits
// Can use acceptance masks
// Different priority interrupts
// Support for more interrupt types
// 	System level interrupts
// Error checking
// Timer functions
 *
 * Concerns:
 * 	Updating data for sending
 *
 * @file main.c
 * @author Ricky Liou <rliou92@gmail.com> 404-451-7986
 * @brief This file contains the CAN API for the microcontrollers to communicate with each other.
 * @warning Has not been thoroughly tested, might have bugs.
 * @ingroup CAN
 *
//###########################################################################*/


#include "DSP28x_Project.h"
#include "can.h"


//USER DEFINED CAN_INFO ARRAY
void imu_send_isr(){}
void imu_receive_isr(CAN_ID ID, int dataH, int dataL, int mbox_num){}
CAN_INFO CAN_INFO_ARRAY[] = {
		{
				IMU,
				&imu_send_isr,
				&imu_receive_isr
		}
};

/*
@brief Initializes the CAN module
*/

void CAN_init(){
	struct ECAN_REGS ECanaShadow;
	//CAN_INFO_ARRAY[ID].upon_sent_isr = send_isr;
	//CAN_INFO_ARRAY[ID].upon_receive_isr = receive_isr;
	// Step 1. Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	// This function is found in the F2806x_SysCtrl.c file.
	// Should be commented out in regular usage. For normal usage initializing the system should be done elsewhere not in the CAN code.
	// For testing purposes this is uncommented to initialize the system.
	   InitSysCtrl();

	// Step 2. Initalize GPIO:
	// Configure CAN pins using GPIO regs here
	// This function is found in F2806x_ECan.c
	   InitECanGpio();

	// Step 3. Clear all interrupts and initialize PIE vector table:
	// Disable CPU interrupts
	   DINT;

	// Disable CPU interrupts and clear all CPU interrupt flags:
	   IER = 0x0000;
	   IFR = 0x0000;

	   EALLOW;
	   //Direct ECANA0 interrupts to the proper isr
	   PieVectTable.ECAN0INTA = &ecan_isr;
	   EDIS;

	// Enable the PIE Vector Table
	   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

   // Step 4. Initialize CAN module
	   InitECana();

	   EALLOW;
	   //Allow all mailboxes to send interrupts
	   ECanaRegs.CANMIM.all = 0xFFFFFFFF;
	   //Disable all other system interrupts (not recommended)
	   //Only enable level 0 interrupts
	   //BY DEFAULT using level 0 CAN interrupts
	   ECanaRegs.CANGIM.all = 0x00000001;
	   // EALLOW;
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	    ECanaShadow.CANMC.bit.STM = 1;    // Configure CAN for self-test mode
	    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
	    //EDIS;
	   EDIS;

	   //CAN interrupts are part of IER 9
	    IER |= M_INT9;

	    //Enable ECAN interrupt 0 in PIE
	    PieCtrlRegs.PIEIER9.bit.INTx5 = 1;

	    // Enable global Interrupts and higher priority real-time debug events:
	    EINT;   // Enable Global interrupt INTM
	    ERTM;   // Enable Global realtime interrupt DBGM
}

//@brief Data must be array of {Lower 4 bytes, Higher 4 bytes, etc}
//Sends data starting from specified mailbox. No error checking in place yet. Careful not to exceed 31!
//Length is in units of bytes.
//Data must be multiple of 8 bytes, even if you're not sending 8 bytes!
//Data is sent starting from lower 4 bytes.
//	Ex: PEDALS sends out 4 bytes of data from mailbox 4 + 5
//	CAN_SEND(data_array_pointer, 4, PEDALS, 4);
void CAN_send(Uint32* data, Uint32 length, CAN_ID ID, int mbox_num){
	struct ECAN_REGS ECanaShadow;
	Uint32 numMbox; //How many mailboxes need to be used?
	if(length%8){
		numMbox = length/8 + 1;
	}
	else{
		numMbox = length/8;
	}

	Uint32 bitMaskOfOnes = ((1 << (numMbox)) - 1) << (mbox_num);

	//ECanaRegs.CANTRR.all |= bitMaskOfOnes; //Clear TRS bits
	ECanaShadow.CANTRR.all = ECanaRegs.CANTRR.all;
	ECanaShadow.CANTRR.all |= bitMaskOfOnes;
	ECanaRegs.CANTRR.all = ECanaShadow.CANTRR.all;

	while(ECanaRegs.CANTRS.all & bitMaskOfOnes); //Wait until TRS bits are cleared

	//ECanaRegs.CANME.all &= ~bitMaskOfOnes; //Disable the mailboxes to modify their content
	ECanaShadow.CANME.all = ECanaRegs.CANME.all;
	ECanaShadow.CANME.all &= ~bitMaskOfOnes;
	ECanaRegs.CANME.all = ECanaShadow.CANME.all;

	volatile struct MBOX *Mailbox;

	//ECanaRegs.CANMD.all &= ~bitMaskOfOnes; //Configure mailboxes for transmit
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
	ECanaShadow.CANMD.all &= ~bitMaskOfOnes;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;

	Uint32 i;
	for (i=0; i< numMbox; i++){
		Mailbox = &ECanaMboxes.MBOX0 + i + mbox_num;

		if(length >= 8){
			Mailbox->MSGCTRL.bit.DLC = 8;
			length -= 8;
		}
		else{
			Mailbox->MSGCTRL.bit.DLC = length;
		}

		Mailbox->MDL.all = data[i];
		Mailbox->MDH.all = data[i+1];
		Mailbox->MSGID.all = ((Uint32) 0x4 << 29) | (Uint32) ID; // The ID is only the last 28 bits. ID cannot be greater than 2^29.
		//I am using the extended identifier. I don't really understand the other modes at this point. Better to stick to what I know for now.
	}
	//ECanaRegs.CANME.all |= bitMaskOfOnes; //Enable the mailboxes
	ECanaShadow.CANME.all = ECanaRegs.CANME.all;
	ECanaShadow.CANME.all |= bitMaskOfOnes;
	ECanaRegs.CANME.all = ECanaShadow.CANME.all;

	//ECanaRegs.CANTRS.all |= bitMaskOfOnes; //Send the data all at once!
	ECanaShadow.CANTRS.all = ECanaRegs.CANTRS.all;
	ECanaShadow.CANTRS.all |= bitMaskOfOnes;
	ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

}

/*
 * @brief Configure specified mailbox to receive *length* bytes from desired CAN ID
 */
void CAN_receive(CAN_ID ID, int length, int mbox_num){
	volatile struct MBOX *Mailbox;
	struct ECAN_REGS ECanaShadow;

	Mailbox = &ECanaMboxes.MBOX0 + mbox_num;
	Uint32 mbox_mask = 1 << mbox_num;

	//ECanaRegs.CANME.all &= ~mbox_mask; //Disable the mailboxes to modify their content
	ECanaShadow.CANME.all = ECanaRegs.CANME.all;
	ECanaShadow.CANME.all &= ~mbox_mask;
	ECanaRegs.CANME.all = ECanaShadow.CANME.all;

	Mailbox->MSGID.all = ((Uint32) 0x4 << 29) | (Uint32) ID; // The ID is only the last 28 bits. ID cannot be greater than 2^29.

	//ECanaRegs.CANMD.all |= mbox_mask; //Configure mailbox for receive
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
	ECanaShadow.CANMD.all |= mbox_mask;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;

	Mailbox->MSGCTRL.bit.DLC = length;

	//ECanaRegs.CANME.all |= mbox_mask; //Enable the mailboxes
	ECanaShadow.CANME.all = ECanaRegs.CANME.all;
	ECanaShadow.CANME.all |= mbox_mask;
	ECanaRegs.CANME.all = ECanaShadow.CANME.all;

}
/*
 * @brief Request data from specified mailbox
 * length is in bytes
 */
void CAN_request(CAN_ID ID, int length, int mbox_num){
	struct ECAN_REGS ECanaShadow;
	volatile struct MBOX *Mailbox;
	Mailbox = &ECanaMboxes.MBOX0 + mbox_num;
	int mbox_mask = 1 << mbox_num;

	//ECanaRegs.CANME.all &= ~mbox_mask; //Disable the mailboxes to modify their content
	ECanaShadow.CANME.all = ECanaRegs.CANME.all;
	ECanaShadow.CANME.all &= ~mbox_mask;
	ECanaRegs.CANME.all = ECanaShadow.CANME.all;

	Mailbox->MSGID.all = ((Uint32) 0x4 << 29) | (Uint32) ID; // The ID is only the last 28 bits. ID cannot be greater than 2^29.

	//ECanaRegs.CANMD.all |= mbox_mask; //Configure mailbox for receive
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
	ECanaShadow.CANMD.all |= mbox_mask;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;

	Mailbox->MSGCTRL.bit.DLC = length;
    Mailbox->MSGCTRL.bit.RTR = 1;//Set request flag

    //ECanaRegs.CANME.all |= mbox_mask; //Enable the mailboxes
	ECanaShadow.CANME.all = ECanaRegs.CANME.all;
	ECanaShadow.CANME.all |= mbox_mask;
	ECanaRegs.CANME.all = ECanaShadow.CANME.all;

	//ECanaRegs.CANTRS.all |= mbox_mask;//Request!
	ECanaShadow.CANTRS.all = ECanaRegs.CANTRS.all;
	ECanaShadow.CANTRS.all |= mbox_mask;
	ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;
}

// @brief Set up a mailbox to automatically send data upon request. Length in bytes.

void CAN_autoreply(Uint32* data, Uint32 length, CAN_ID ID, int mbox_num){
	struct ECAN_REGS ECanaShadow;
	volatile struct MBOX *Mailbox;

	Uint32 numMbox; //How many mailboxes need to be used?
	if(length%8){
		numMbox = length/8 + 1;
	}
	else{
		numMbox = length/8;
	}

		Uint32 bitMaskOfOnes = ((1 << (numMbox)) - 1) << (mbox_num);

		//ECanaRegs.CANTRR.all |= bitMaskOfOnes; //Clear TRS bits
		ECanaShadow.CANTRR.all = ECanaRegs.CANTRR.all;
		ECanaShadow.CANTRR.all |= bitMaskOfOnes;
		ECanaRegs.CANTRR.all = ECanaShadow.CANTRR.all;

		while(ECanaRegs.CANTRS.all & bitMaskOfOnes); //Wait until TRS bits are cleared

		//ECanaRegs.CANME.all &= ~bitMaskOfOnes; //Disable the mailboxes to modify their content
		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
		ECanaShadow.CANME.all &= ~bitMaskOfOnes;
		ECanaRegs.CANME.all = ECanaShadow.CANME.all;

		//ECanaRegs.CANMD.all &= ~bitMaskOfOnes; //Configure mailboxes for transmit
		ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
		ECanaShadow.CANMD.all &= ~bitMaskOfOnes;
		ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;

		int i;
		for (i=0; i< numMbox; i++){
				Mailbox = &ECanaMboxes.MBOX0 + i + mbox_num;

				if(length >= 8){
					Mailbox->MSGCTRL.bit.DLC = 8;
					length -= 8;
				}
				else{
					Mailbox->MSGCTRL.bit.DLC = length;
				}
			Mailbox->MDL.all = data[i];
			Mailbox->MDH.all = data[i+1];
			Mailbox->MSGID.all = ((Uint32) 0x5 << 29) | (Uint32) ID; // The ID is only the last 28 bits. ID cannot be greater than 2^29.
			//I am using the extended identifier. I don't really understand the other modes at this point. Better to stick to what I know for now.
			//Auto answer mode enabled!
		}
		//ECanaRegs.CANME.all |= bitMaskOfOnes; //Enable the mailboxes
		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
		ECanaShadow.CANME.all |= bitMaskOfOnes;
		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
}

//@brief Based on the the event which triggered the interrupt (sent or received), calls the user specified function

__interrupt void ecan_isr(void){
	//Extract mailbox number, CAN ID, data, execute desired user function

	Uint32 CAN_ARRAY_LENGTH, i;
	CAN_ARRAY_LENGTH = sizeof CAN_INFO_ARRAY / sizeof CAN_INFO_ARRAY[0];
	CAN_ID ID;
	volatile struct MBOX *Mailbox;

	//Determine which mailbox generated the interrupt
	Uint16 mbox_num = ECanaRegs.CANGIF0.bit.MIV0;
	Mailbox = &ECanaMboxes.MBOX0 + mbox_num;
	Uint32 mbox_mask = 1 << mbox_num;

	ID = (CAN_ID) (Mailbox->MSGID.all & 0x1FFFFFFF); //The ID is only the last 29 bits.

	for(i=0; i< CAN_ARRAY_LENGTH; i++){
		if(CAN_INFO_ARRAY[i].ID == ID){
			if(ECanaRegs.CANTA.all & mbox_mask){ //If TA bit is set
				CAN_INFO_ARRAY[i].upon_sent_isr();
				ECanaRegs.CANTA.all &= ~mbox_mask; //Clear TA bit
			}
			else if(ECanaRegs.CANRMP.all & mbox_mask){ //If RMP bit is set
				CAN_INFO_ARRAY[i].upon_receive_isr(ID, Mailbox->MDH.all, Mailbox->MDL.all, mbox_num);
				ECanaRegs.CANRMP.all &= ~mbox_mask; //Clear RMP bit
			}
		}
	}

	PieCtrlRegs.PIEACK.bit.ACK9 = 1; //Acknowledge interrupt
}
