#include <Arduino.h>
#include "../../APP_Cfg.h"
#include "../../Hal/SensorH/SensorH.h"
#include "POT.h"



#if POT_DEBUG == STD_ON
#define DEBUG_PRINTLN(var) Serial.println(var)
#define DEBUG_PRINT(var) Serial.print(var)
#else
#define DEBUG_PRINTLN(var)
#define DEBUG_PRINT(var)
#endif



//Globals
static SensorH_t config = {.channel=POT_PIN, .resolution=POT_RESOLUTION};
static uint16_t pot_value = 0;

//static functions

void POT_init(void)
{
#if POT_ENABLED==STD_ON
    SensorH_Init(&config);
#endif
}

void POT_main()
{
#if POT_ENABLED==STD_ON
    pot_value = SensorH_ReadValue(config.channel);
    DEBUG_PRINT("POT Value: ");DEBUG_PRINTLN(pot_value);
    delay(1000);
#endif
}


uint16_t POT_getValue(void)
{
#if POT_ENABLED==STD_ON
    //Function to get POT value if needed elsewhere
    return pot_value;
#else
    return -1;
#endif
}







