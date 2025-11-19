#include <Arduino.h>
#include"UART.h"
#include<WiFi.h>
#include"SIM.h"
#include<TinyGSM.h>

#define GSM_PIN ""
HardwareSerial SerialAT(2);      
TinyGsm modem(SerialAT);          
TinyGsmClient client(modem);      

sim_state_t state = STATE_MODEM_RESTART;
const char* recipientNumber = "+201069587284"; // Replace with the actual phone number
const char* messageContent = "Hello from SIM800L!";

void SIM_Init(void)
{
  Serial.println("[SIM_INIT] Starting Serial...");
  Serial.begin(9600);
    SerialAT.begin(SIM_BAUDRATE, SERIAL_8N1, SIM_RX, SIM_TX);
    delay(1000);
}
void SIM_Main(void)
{
  switch(state)
  {
    case STATE_MODEM_RESTART:
    Serial.println("[STATE_MODEM_RESTART] Restarting modem...");
    
    if (!modem.init())
    {
      Serial.println("Restart failed!");
      state = STATE_ERROR;
      delay(1000);
    }
    else
    {
      Serial.println("Modem ready.");
      state = STATE_CHECK_SIM;
      if (GSM_PIN && modem.getSimStatus() != 3) { 
      modem.simUnlock(GSM_PIN); 
      }
      
    }
    break;
    
    case STATE_CHECK_SIM:
    {
    Serial.println("[STATE_CHECK_SIM] Checking SIM card...");
    int status = modem.getSimStatus();
    if (status != SIM_Ready)  
    {
      Serial.println("SIM not ready! Status: " + String(status));
      delay(1000);
      state = STATE_ERROR;
    }
    else
    {
      Serial.println("SIM detected.");
      state = STATE_WAIT_NETWORK;
    }
    break;
    }
    case STATE_WAIT_NETWORK:
    Serial.println("[STATE_WAIT_NETWORK] Waiting for network...");
    if (modem.waitForNetwork(10000))
    {
      Serial.println("Connected to network.");
      state = STATE_GPRS_CONNECT;
    }
    else
    {
      Serial.println("Network not found!");
      state = STATE_ERROR;
    }
    break;
    case STATE_GPRS_CONNECT:
    {
    Serial.println("[STATE_GPRS_CONNECT] Connecting GPRS...");
    uint8_t sq = modem.getSignalQuality();
    Serial.println("Signal Quality is : ");Serial.println(sq);
    if (!modem.gprsConnect("internet", "", ""))   
    {
      Serial.println("GPRS failed!");
      state = STATE_ERROR;
    }
    else
    {
      Serial.println("GPRS connected.");
      state = STATE_SEND_MASSAGE;
    }    
    break;
    }
   case STATE_SEND_MASSAGE:
    if (modem.sendSMS(recipientNumber, messageContent)) {
        Serial.println("SMS sent successfully!");
    } else {
        Serial.println("Failed to send SMS.");
        state = STATE_ERROR;
    }
    break;

    case STATE_IDLE:
    Serial.println("[STATE_IDLE] Done. Restarting the state machine in 5 seconds...");
    delay(5000);
    state = STATE_MODEM_RESTART;
    break;
    case STATE_ERROR:
    Serial.println("[STATE_ERROR] ERROR occurred! Retrying in 5 seconds...");
    delay(5000);
    state = STATE_MODEM_RESTART;
    break;



  }

}

void setup() {
  SIM_Init();

}

void loop() {
  SIM_Main();

}
