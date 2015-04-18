import jssc.*;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Timer;
import java.util.TimerTask;
//import java.io.PrintWriter;//IN ANTICIPATION OF SAVEDATA() FUNCTION
//import java.io.FileNotFoundException;

/**
 *This class is designed to receive data sent over WiFi and pass it to/interact with elements of a gui
 *
 *@author PK
 */
public class WiFiSerial {


	private static SerialPort serialPort;
	private static byte[][] messages;

	/**
	 * Setup serial port.
	 */
	public static void init() {
		//Initialize datastructure
		messages = new byte[12][];

		//Make sure only one serial device is connected
		SerialPortList spl = new SerialPortList();
		String[] portNames = spl.getPortNames();
		if (portNames.length==0) {
			LogPanel.println("Serial device not connected. Connect and wait five seconds to proceed.");
		} else if (portNames.length!=1) {
			LogPanel.println("Too many serial ports connected. Disconnect all not connected to the wireless module");
		}
		while (portNames.length!=1) {
			portNames = spl.getPortNames();
			try {
				Thread.sleep(5000);
			} catch (InterruptedException ex) { 
				LogPanel.println("Who hath disturbed my slumber?"); 
			}
		}

		//Setup the serial connection
		serialPort = new SerialPort(portNames[0]);
		try {
			LogPanel.println("Port opened: " + serialPort.openPort());
			LogPanel.println("Params set: " + serialPort.setParams(115000, 8, 1, 0));//setParams(int baudRate, int dataBits, int stopBits, int parity)
		}
		catch (SerialPortException ex) {
			LogPanel.println("SerialPortException");
		}
	}

	/**
	 * Update the recieved-data byte array (messages)
	 * packet format is:
	 * 			[talomere][enum type][length][message]
	 *			<---10---><----1----><---1--><---X--->
	 *				^underscores
	 * There are multiple packets in each new full read
	 */
	public static void read() {//called once per second
		byte[] full = null;
		try {
			full = serialPort.readBytes();
		} catch (SerialPortException ex) {
			LogPanel.println("SerialPortException");
		}
		if (full==null) {
			LogPanel.print("No data. ");
			return;
		}
		int device, len;
		for (int i=0; i<full.length; i+=len) {//while not iterated through all new packets
			while (((char)full[i])=='_') {//eat talomere (only at beginning of packet, not during messages)
				i++;						//this all may be unnecessary
			}
			device = full[i];	//assume first byte after talomere is the enum type
			len = full[i+1];	//second must be length (only up to 255 here)
			i+=2;				//skip over header
			if (messages[device]==null) {	//if byte array not initialized
				messages[device] = new byte[len];	//then initialize to length
			}
			for (int j=0; j<len; j++) {		//copy all the data from the message
				messages[device][j] = full[i+j];
			}
		}
	}

	/**
	 * Return the data pertaining to a given device.
	 */
	public static byte[] read(Device ID) {
		if (messages==null) { return null; }
		return messages[ID.ordinal()];
	}

	public void receiveData(HashMap<String,LinkedList<Float>> map, int maxLength){
		try {
			String receive = serialPort.readString(); 
			String[] parts = receive.split(";");
			LinkedList<Float> addTo = map.get(parts[0]);
			for(int i=1; i < parts.length; i++){
				addTo.addLast(Float.parseFloat(parts[i]));
				if (addTo.size()==maxLength){
					addTo.removeFirst();
				}
			}
		}
		catch (SerialPortException e) {
			// TODO Auto-generated catch block
			LogPanel.println("SerialPortException");
			e.printStackTrace();
		}		
	}

	/**
	 * Close the serial port.
	 */
	public static void close() {
		try {
			LogPanel.println("Port closed: " + serialPort.closePort());
		} catch (SerialPortException ex) {
			LogPanel.println("SerialPortException");
		}
	}
}