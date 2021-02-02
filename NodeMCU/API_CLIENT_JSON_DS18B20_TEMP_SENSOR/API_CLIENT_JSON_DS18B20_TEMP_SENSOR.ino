#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <OneWire.h>
#include "config.h"

OneWire ds(DHTPin);

#include "WifiConnection.hpp"

void setup() {
  Serial.begin(9600);

    pinMode(CONNECTED_LED, OUTPUT);
    pinMode(CONNECTING_LED, OUTPUT);
    pinMode(FAIL_REQUEST_LED, OUTPUT);
    pinMode(SEND_REQUEST_LED, OUTPUT);

  if (!connectToWifi()) {
    ESP.restart();
  }
}

void loop() {
    updateMeasurement();
    delay(30000); // Prueba, sustituir con valor real después
}

float getTemp() {
  byte data[12];
  byte addr[8];

  if(!ds.search(addr)) {
    ds.reset_search();
    return -1000;
  }

  if(OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid");
    return -1000;
  }

  if(addr[0] != 0x10 && addr[0] != 0x28) {
    Serial.print("Device is not recognized");
    return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);

  byte present = ds.reset();
  ds.select(addr);
  ds.write(0xBE);

  for (int i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB);
  float temperatureSum = tempRead / 16;
  return temperatureSum;
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

    HTTPClient http;
    http.begin(HEFESTO_SERVER);
    http.addHeader("Content-Type", "application/json");
    
    String body = "";
    float temperature = getTemp();
    StaticJsonDocument<64> jsonRequest;
    jsonRequest["temperature"] = temperature;
    serializeJson(jsonRequest, body);

    int httpCode = http.PUT(body);

    if (httpCode == 200) {
        Serial.print(httpCode);
        sendRequestLedOff();
    } else {
        Serial.print(httpCode);
        failRequestLedOn();
        delay(10000);
        failRequestLedOff();
    }
}
