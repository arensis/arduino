void printWifiConnectionDetails() {
  Serial.println("");
  Serial.print("Conectado a:\t");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address:\t");
  Serial.println(WiFi.localIP());
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("La intensidad de la señal es:\t");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

bool connectToWifi() {
  connectingLedOn();
  
  WiFi.hostname(HOST_NAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, PASSWORD);

  connectingLedOn();

  for (int i = 0; i < WIFI_CONNECTION_TIME_OUT; i++) {
    connectingLedOn();
    if (WiFi.status() == WL_CONNECTED) {
      printWifiConnectionDetails();
      connectionSuccessLedOn();
      return true;
    }

    Serial.print(".");
    delay(500);
  }

  failConnectionLedOn();
  return false;
}

void restartOnConnectionFailure() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wifi check: Connected");
  } else {
    Serial.println("Wifi check: Not Connected");
    ESP.restart();
  }
}
