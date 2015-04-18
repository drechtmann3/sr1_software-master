#ifndef THREADS_H
#define THREADS_H

//function declarations
void *motor_thread(int *x);
void *airgap_thread(int *x);
void *pedalAvg_thread(int *x);

#endif
