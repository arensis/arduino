/**
 * Sensor pin configuration
 */
const int DHTPin = 14; // D5 of NodeMCU is GPIO14
const int CONNECTING_LED = 0; //D3 of NodeMCU is GPIO0
const int CONNECTED_LED = 5; //D1 of NodeMCU is GPIO5
const int SEND_REQUEST_LED = 4; //D2 of NodeMCU is GPIO4
const int FAIL_REQUEST_LED = 12; //D6 of NodeMCU is GPI12

/**
 * Wifi connection configuration
 */
const char* WIFI_SSID = "ssid";     // The name of the network to connect
const char* PASSWORD = "password";  // The password of the network to connect
const char* HOST_NAME = "HomeStation"; // Name of the device in your network
int WIFI_CONNECTION_TIME_OUT = 100; // Timeout to connect to the WiFi

/**
 * API REST Server configuration
 */

