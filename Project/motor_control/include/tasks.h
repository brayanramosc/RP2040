#ifndef _TASKS_H
#define _TASKS_H

#define MIN_PWM     16
#define MAX_PWM     100
#define MIN_RPM     20
#define MAX_RPM     220
#define DU          MAX_PWM - MIN_PWM
#define DY          MAX_RPM - MIN_RPM
#define GAIN        DY / DU

void getBytesTask (void * );
void openLoopTask (void *);
void createTasks (void);

#endif
