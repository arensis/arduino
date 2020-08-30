/**
 * Sensor pin configuration
 */
const int DHTPin = 14; // D5 of NodeMCU is GPIO14

/**
 * Wifi connection configuration
 */
const char* WIFI_SSID = "ssid";     // The name of the network to connect
const char* PASSWORD = "password";  // The password of the network to connect
const char* HOST_NAME = "HomeStation"; // Name of the device in your network
int WIFI_CONNECTION_TIME_OUT = 100; // Timeout to connect to the WiFi

/**
 * HTTP Server configuration
 */
const byte HTTP_SERVER_PORT = 80;
