#include <DHTesp.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "config.h"

DHTesp dht;

#include "WifiConnection.hpp"

void setup() {
  Serial.begin(115200);

    pinMode(CONNECTED_LED, OUTPUT);
    pinMode(CONNECTING_LED, OUTPUT);
    pinMode(FAIL_REQUEST_LED, OUTPUT);
    pinMode(SEND_REQUEST_LED, OUTPUT);

  if (!connectToWifi()) {
    ESP.restart();
  }
  dht.setup(DHTPin, DHTesp::DHT11);
}

void loop() {
    updateMeasurement();
    delay(30000); // Prueba, sustituir con valor real después
}

void sendRequestLedOn() {
    digitalWrite(SEND_REQUEST_LED, HIGH);
}

void sendRequestLedOff() {
    digitalWrite(SEND_REQUEST_LED, LOW);
}

void failRequestLedOn() {
    digitalWrite(FAIL_REQUEST_LED, HIGH);
}

void failRequestLedOff() {
    digitalWrite(FAIL_REQUEST_LED, LOW);
}

void updateMeasurement() {
    sendRequestLedOn();
    
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();

    HTTPClient http;
    http.begin(HEFESTO_SERVER);
    http.addHeader("Content-Type", "application/json");
    
    String body = "";
    StaticJsonDocument<64> jsonRequest;
    jsonRequest["temperature"] = temperature;
    jsonRequest["humidity"] = humidity;
    serializeJson(jsonRequest, body);

    int httpCode = http.PUT(body);

    if (httpCode == 201) {
        Serial.print(httpCode);
        sendRequestLedOff();
    } else {
        Serial.print(httpCode);
        failRequestLedOn();
        delay(10000);
        failRequestLedOff();
    }
}
