#include <Arduino.h>
#include "src/APP_Cfg.h"
#include "src/App/POT/POT.h"
#include "src/App/LM35/LM35.h"
#include "src/Hal/UART/UART.h"
#include "src/Hal/GSM/GSM.h"


#define GSM_UART   UART1


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  UART_init();
    delay(2000);

    Serial.println("Initializing GSM...");

    // Initialize GSM (creates TinyGSM modem + UART)
    GSM_init(GSM_UART);

    // Connect to network
    GSM_Status_t net = GSM_connectNetwork("internet", "", "");
    if (net != GSM_STATUS_OK) {
        Serial.println("Network connection failed!");
        return;
    }

    Serial.println("Network Connected!");

    // Send SMS
    GSM_Status_t sms = GSM_sendSMS("+201120076894", "Hello from ESP32 + SIM800L!");
    if (sms == GSM_STATUS_OK) {
        Serial.println("SMS sent!");
    } else {
        Serial.println("SMS FAILED!");
    }
  
}

void loop() {
  POT_main();
  LM35_main();
}