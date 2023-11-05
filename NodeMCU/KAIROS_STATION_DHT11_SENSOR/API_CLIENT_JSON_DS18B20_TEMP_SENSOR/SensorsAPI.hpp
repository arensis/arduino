DHTesp dht;

void waitDhtMinimumSamplingPeriod() {
  delay(dht.getMinimumSamplingPeriod());
}

float buildHumidity() {
  return dht.getHumidity();
}

float buildTemperature() { 
  return dht.getTemperature();
}

void initSensorsSetup() {
  dht.setup(DHTPin, DHTesp::DHT11);    
}
