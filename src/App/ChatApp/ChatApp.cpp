#include <Arduino.h>
#include "../../APP_Cfg.h"
#include "../../Hal/UART/UART.h"
#include "ChatApp.h"



#if ChatApp_DEBUG == STD_ON
#define DEBUG_PRINTLN(var) Serial.println(var)
#else
#define DEBUG_PRINTLN(var)
#endif


//Statc variables
static const String password = "12345";
static bool flag = false;


//Static functions
void ChatApp_Authenticate(String pass);


void ChatApp_Authenticate(String pass)
{
#if ChatApp_ENABLED == STD_ON
    if(password == pass)
    {
        flag = true;
    }
    else
    {
        flag = false;
    }
#endif
}


void ChatApp_main_4s(void)
{
#if ChatApp_ENABLED == STD_ON
    String payload = "";
    if(flag == true)
    {
        if (Serial.available() > 0) 
        {
            String incomingBytes = Serial.readStringUntil('\n');
            DEBUG_PRINTLN("I received: ");
            DEBUG_PRINTLN(incomingBytes);DEBUG_PRINTLN(DEC); 
            UART_write(UART1,incomingBytes.c_str());
        }


        UART_read(UART1,payload);
        if(payload != "")
        {
            Serial.println("Echo: " + payload);
        }
        
    }
    else
    {
        DEBUG_PRINTLN("Authentication Failed. Access Denied.");
        UART_read(UART1,payload);
        if(payload != "")
        {
            Serial.println("Echo: " + payload);
        }
        ChatApp_Authenticate(payload);
    }
    delay(4000);
#endif
}






