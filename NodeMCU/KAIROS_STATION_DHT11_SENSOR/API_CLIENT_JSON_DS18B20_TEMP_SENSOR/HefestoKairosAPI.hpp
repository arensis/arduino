WiFiClientSecure client;

void setHefestoKariosFingerPrint() {
  client.setFingerprint(fingerprint);
}

String httpsPut(String data) {
  Serial.println("Complete hefest-karios url");
  Serial.println(HEFESTO_KAIROS_HOST + HEFESTO_KAIROS_PATH);
  
  if (client.connect(HEFESTO_KAIROS_HOST, 5000)) {
    client.println("PUT " + HEFESTO_KAIROS_PATH + " HTTP/1.1");
    client.println("Host: " + (String)HEFESTO_KAIROS_HOST);
    client.println("User-Agent: ESP8266/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/json;");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);
    delay(10);
    String response = client.readString();
    return response;
  }
  else {
    return "ERROR kairos-server connection";
  }
}

int handleResponse(String response, String body) {
  Serial.println("Handling response: ");

  Serial.println("Response: ");
  Serial.println(response);
  
  int responseCode = response.substring(9, 12).toInt();

  if(responseCode == 201) {
    Serial.print(response);
    Serial.println(body);
    sendRequestLedOff();
  } else {
    Serial.println("----- ERROR SENDING TEMPERATURES -----");
    Serial.print("Response code: ");
    Serial.println(response);
    Serial.println("--------------------------------------");
    sendFailureToTelegramBot(body, response);
    sendRequestLedOff();
    failRequestLedOn();
  }

  delay(3 * 1000);
  failRequestLedOff(); 

  return responseCode;  
}

void updateMeasurement(float humidity, float temperature) {
    sendRequestLedOn();
    
    restartOnConnectionFailure();
     
    String body = "";
    StaticJsonDocument<64> jsonRequest;
    jsonRequest["temperature"] = temperature;
    jsonRequest["humidity"] = humidity;      
    serializeJson(jsonRequest, body);
    Serial.println("Sending request, request: body:");
    Serial.println(body);

    String response = httpsPut(body);

    int responseCode = handleResponse(response, body);

    if (responseCode != 201) {
      updateMeasurement(humidity, temperature);
    }

    delay(MEASURE_WAITING_TIME);
}
