

#include <ESP8266WiFi.h>
#include <OneWire.h>
#include "config.h"
#define DS18B20 2

OneWire ds(DS18B20);

long timeoutTime = 2000;

WiFiServer server(serverPort);
WiFiClient client;

void setup() {
  Serial.begin(9600);

  WiFi.hostname(hostName);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  printWifiConnectionDetails();
  server.begin();
}

void loop() {
  client = server.available();

  if (client) {
    Serial.println("Nuevo cliente");
    long currentTime = millis();
    long previousTime = currentTime;
    int loadedPage = 0;
    
    while (client.connected() && currentTime - previousTime <= timeoutTime ) {
      currentTime = millis();
      if (client.available()) {
        if(loadedPage == 0) {
          printResponse();
          loadedPage = 1;
        }
      }
    }
  }
}

void printResponseHeaders() {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();
}

void printResponseBody() {
  client.println("{temperature: " + String(getTemp()) + "}");
  client.println();
  delay(100);
}

void printResponse() {
  printResponseHeaders();
  printResponseBody();
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

void printWifiConnectionDetails() {
  Serial.println("");
  Serial.print("Conectado a: ");
  Serial.println(WiFi.SSID());
  Serial.print("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("");
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("");
  Serial.print("La intensidad de la señal es: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}
