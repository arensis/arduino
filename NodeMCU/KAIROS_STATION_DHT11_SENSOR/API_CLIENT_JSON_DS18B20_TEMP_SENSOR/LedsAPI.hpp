void initLedSetup() {
  pinMode(CONNECTED_LED, OUTPUT);
  pinMode(CONNECTING_LED, OUTPUT);
  pinMode(FAIL_REQUEST_LED, OUTPUT);
  pinMode(SEND_REQUEST_LED, OUTPUT);
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

void connectingLedOn() {
    digitalWrite(CONNECTING_LED, HIGH);
    delay(1000);
    digitalWrite(CONNECTING_LED, LOW);
    delay(1000);
}

void failConnectionLedOn() {
  digitalWrite(CONNECTING_LED, HIGH);
}

void connectionSuccessLedOn() {
  digitalWrite(CONNECTED_LED, HIGH);
}
