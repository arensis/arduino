#include "Fetch.h"
#include <DHTesp.h>
#include <ESP8266WiFi.h> //Board driver version 2.7.4
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "CTBot.h"

#include "config.h"
#include "LedsAPI.hpp"
#include "SensorsAPI.hpp"
#include "WifiConnection.hpp"
#include "TelegramAPI.hpp"
#include "HefestoKairosAPI.hpp"

unsigned long (MILLIS);

void setup() {
  Serial.begin(9600);

  initLedSetup();
  initSensorsSetup();

  if (!connectToWifi()) {
    ESP.restart();
  }

  connectTelegramAPI();
  sendTelegramMessage("Kairos station on - notification on");
  setHefestoKariosFingerPrint();
}

void loop() {
    MILLIS = millis();

    if (MILLIS >= (MEASURE_WAITING_TIME * 10)) {
      ESP.restart();
    }

    float humidity;
    float temperature;

    while (humidity == NULL || temperature == NULL) {
      waitDhtMinimumSamplingPeriod();
      humidity = buildHumidity();
      temperature = buildTemperature();
    }
    
    updateMeasurement(humidity, temperature);
}
