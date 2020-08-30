void getRequest() {
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);

  WeatherStationWebContent webContent = WeatherStationWebContent("Oficina", humidity, temperature, heatIndex);

  serverHTTP.send(200, "text/html", webContent.getWebContent());
}

void initHTTPServer() {
  serverHTTP.on("/", HTTP_GET, getRequest);
  serverHTTP.begin();
  Serial.println();
  Serial.println("Servidor HTTP inicializado");
}
