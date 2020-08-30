#include <DHTesp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "config.h"

DHTesp dht;
ESP8266WebServer serverHTTP(HTTP_SERVER_PORT);

#include "WeatherStationWebContent.hpp"
#include "WifiConnection.hpp"
#include "WebServerController.hpp"

void setup() {
  Serial.begin(9600);

  if (!connectToWifi()) {
    ESP.restart();
  }

  dht.setup(DHTPin, DHTesp::DHT11);
  initHTTPServer();
}

void loop() {
  serverHTTP.handleClient();
}
