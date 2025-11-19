#include <Arduino.h>
#include "../App_cfg.h"
#include "../HAL/SensorH/SensorH.h"

#if LM35_DEUG == STD_ON
#define DEBUG_PRINTLN(var) Serial.println(var)
#else
#define DEBUG_PRINTLN(var)
#endif

// Sensor object
static SensorH_t config = {LM35_ADC_PIN, POT_RESOLUTION};
static uint16_t LM_value;

void LM35_Init(void)
{
#if LM35_ENABLED == STD_ON
    SensorH_Init(&config);
#endif
}

float LM35_ReadTempC(void)
{
#if LM35_ENABLED == STD_ON

    LM_value = SensorH_ReadValue(config.channel);
    float voltage = ((float)LM_value * LM35_VREF) / LM35_ADC_MAX;
    float tempC = voltage * 100.0f;
    DEBUG_PRINTLN("TEMP_value: ");
    DEBUG_PRINTLN(tempC);
    return tempC;
#endif
}

float LM35_ReadTempF(void)
{
#if LM35_ENABLED == STD_ON
    float tempC = LM35_ReadTempC();
    float tempF = (tempC * 9.0f / 5.0f) + 32.0f;
    DEBUG_PRINTLN("TEMP_value: ");
    DEBUG_PRINTLN(tempF);
    return tempF;
#endif
}
