CTBot myBot;

void connectTelegramAPI() {
  myBot.wifiConnect(WIFI_SSID, PASSWORD);
  myBot.setTelegramToken(TELEGRAM_TOKEN);  
}

void sendTelegramMessage(String message) {
  myBot.sendMessage(TELEGRAM_CHAT_ID, message);
  /*
  String url = "https://api.telegram.org/bot" + TELEGRAM_TOKEN + "/sendMessage?chat_id=" + TELEGRAM_CHAT_ID + "&text=" + message;
  Serial.println("TELEGRAM Request URL: " + url);
  HTTPClient http;
  http.begin(url);
  char httpCode = http.GET();
  Serial.println("---- TELEGRAM MENSAJE RESPONSE ----");
  Serial.println("Status code: " + httpCode);
  Serial.println("-----------------------------------");
  */
}


void sendFailureToTelegramBot(String body, String errorCode) {
  String message = (String)"Sensor status: " + dht.getStatus() + (String) + "\r Response: " + errorCode + "body: " + body;
  sendTelegramMessage(message);
}
