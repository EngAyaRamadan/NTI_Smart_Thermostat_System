#ifndef DIMALARM_H
#define DIMALARM_H


typedef enum {
    DIMALARM_STATE_LOW_ALARM = 0,
    DIMALARM_STATE_HIGH_ALARM,
    DIMALARM_STATE_NORMAL
} DimAlarmState_t;

void DimAlarm_init(void);

void DimAlarm_main(void);

#endif // DIMALARM_H
