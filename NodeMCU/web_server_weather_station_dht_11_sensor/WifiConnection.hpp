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
  WiFi.hostname(HOST_NAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, PASSWORD);

  for (int i = 0; i < WIFI_CONNECTION_TIME_OUT; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      printWifiConnectionDetails();
      return true;
    }

    Serial.print(".");
    delay(500);
  }

  return false;
}
