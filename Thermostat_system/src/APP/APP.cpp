// #include <Arduino.h>
// #include <WiFi.h>
// #include "../App_cfg.h"
// #include "../HAL/GPIO/gpio.h"
// #include "../HAL/SensorH/SensorH.h"
// #include "../HAL/UART/uart.h"
// #include "../HAL/WIFI/wifi.h"
// #include "LED.h"
// #include "POT.h"
// #include "LM35.h"
// #include "ULS.h"

// WIFI_Config_t g_wifiCfg = {
//     .ssid = SSID,
//     .password = PASSWORD,
//     .reconnect_interval_ms = 5000,
//     .on_connect = onWifiConnected,
//     .on_disconnect = onWifiDisconnected};

// void App_init(void)
// {
//     UART_Init();
//     WIFI_Init_(&g_wifiCfg);
//     LED_init(LED_1_PIN);
//     LED_init(LED_2_PIN);
//     LED_init(LED_3_PIN);
//     LM35_Init();
//     POT_init();
//     Ultrasonic_Init();
// }
// void App_main(void)
// {
// }