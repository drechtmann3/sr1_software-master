#ifndef MOTOR_H
#define MOTOR_H

// Motor control state machine.
void *MotorControl(void *thread_id); //clock the motor state machine.
void report_motor_status();
void report_fault_status();

// Airgap functions.
void *AirgapControl(void *thread_id);
int GetGap();

#ifdef ENABLE_MOTOR_KILLSWITCH
int CheckKillswitch (void);
#endif



#endif
