#include <Arduino.h>
#include "src/APP_Cfg.h"
#include "src/App/POT/POT.h"
#include "src/App/LM35/LM35.h"
#include "src/Hal/UART/UART.h"
#include "src/Hal/GSM/GSM.h"
#include "src/App/ChatApp/ChatApp.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  UART_init();
  POT_init();
  LM35_init();  
  
}

void loop() {
  POT_main();
  LM35_main();
  ChatApp_main_4s();
}