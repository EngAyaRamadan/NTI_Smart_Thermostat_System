#include <Arduino.h>
#include <stdint.h>
#include "../../APP_Cfg.h"
#include "../../Hal/GPIO/GPIO.h"
#include "../../Hal/PWM/PWM.h"
#include "../POT/POT.h"
#include "DimAlarm.h"



#if DIMALARM_DEBUG == STD_ON
#define DEBUG_PRINTLN(var) Serial.println(var)
#define DEBUG_PRINT(var) Serial.print(var)
#else
#define DEBUG_PRINTLN(var)
#define DEBUG_PRINT(var)
#endif

static PWM_t pwmConfig = {.channel=DIMER_LED, .frequency=5000, .resolution=8};
static GPIO_t lowAlarmLED = {.pin=ALARM_LOW_LED, .mode=OUTPUT};
static GPIO_t highAlarmLED = {.pin=ALARM_HIGH_LED, .mode=OUTPUT};
static DimAlarmState_t gState = DIMALARM_STATE_NORMAL;
static float potPercentage = 0.0;

//static functions
static void DimAlarm_getState(void);
static void DimAlarm_stateMachine(void);




void DimAlarm_init(void)
{
#if DIMALARM_ENABLED==STD_ON
    PWM_initChannel(&pwmConfig);
    GPIO_initPin(lowAlarmLED.pin, lowAlarmLED.mode);
    GPIO_initPin(highAlarmLED.pin, highAlarmLED.mode);
#endif
}

void DimAlarm_main(void)
{
#if DIMALARM_ENABLED==STD_ON
    uint32_t potValue = POT_getValue();
    potPercentage = (potValue / (float)ADC_MAX_VALUE) * 100.0;
    DEBUG_PRINT("POT Percentage: ");DEBUG_PRINTLN(potPercentage);
    DimAlarm_getState();
    DimAlarm_stateMachine();
#endif
}

static void DimAlarm_getState(void)
{
#if DIMALARM_ENABLED==STD_ON
    if (potPercentage < ALARM_LOW_THRESHOLD_PERCENTAGE) {
        gState = DIMALARM_STATE_LOW_ALARM;
    } 
    else if (potPercentage > ALARM_HIGH_THRESHOLD_PERCENTAGE) {
        gState = DIMALARM_STATE_HIGH_ALARM;
    } 
    else {
        gState = DIMALARM_STATE_NORMAL;
    }
#endif
} 

static void DimAlarm_stateMachine(void)
{
#if DIMALARM_ENABLED==STD_ON
    switch(gState)
    {
        case DIMALARM_STATE_LOW_ALARM:
            GPIO_writePin(lowAlarmLED.pin, HIGH);
            GPIO_writePin(highAlarmLED.pin, LOW);
            PWM_setDutyCycle(pwmConfig.channel, 0.0);
            break;
        case DIMALARM_STATE_HIGH_ALARM:
            GPIO_writePin(lowAlarmLED.pin, LOW);
            GPIO_writePin(highAlarmLED.pin, HIGH);
            PWM_setDutyCycle(pwmConfig.channel, 0.0);
            break;
        case DIMALARM_STATE_NORMAL:
            GPIO_writePin(lowAlarmLED.pin, LOW);
            GPIO_writePin(highAlarmLED.pin, LOW);
            PWM_setDutyCycle(pwmConfig.channel, potPercentage);
            break;
        default:
            break;
    }
#endif
}