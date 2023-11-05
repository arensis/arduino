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
const char* WIFI_SSID = "SSID";     // The name of the network to connect
const char* PASSWORD = "Password";  // The password of the network to connect
const char* HOST_NAME = "Host name"; // Name of the device in your network
int WIFI_CONNECTION_TIME_OUT = 100; // Timeout to connect to the WiFi

/**
 * HEFESTO-KAIROS REST API configuration
 */
String officeStationId = "6321a90407ddd45232f83b82";
String stationID = "MongoDB station id"; // The station id registered on the hefesto-kairos server
#define fingerprint "D8 XX ..." // SHA-1 fingerprint of the ssl certificate
long MEASURE_WAITING_TIME = 30 * 60 * 1000; // The time between measurements in milliseconds
const char* HEFESTO_KAIROS_HOST = "example.com"; // The url base path (host) of the hefesto-kairos server without protocol
String HEFESTO_KAIROS_PATH = "/station/" + stationID + "/measurements"; // The rest of the path to send a measurement 

/**
 * Telegram API configuration
 */
String TELEGRAM_TOKEN = "Telegram token"; //Telegram token provided by them
int TELEGRAM_CHAT_ID = 100000; //Telegram chat id to push new messages
