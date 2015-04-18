#ifndef DATASTORE_H
#define DATASTORE_H
#define CRITICAL (2)
#define ERROR (1)
#define NOTICE (0)

void setThrottle(int in);
int getThrottle();
void setRegenMin(int in);
int getRegenMin();
void setRegenMax(int in);
int getRegenMax();
void setThrottleMin(int in);
int getThrottleMin();
void setThrottleMax(int in);
int getThrottleMax();
void setStep(int in);
int getStep();

#endif
