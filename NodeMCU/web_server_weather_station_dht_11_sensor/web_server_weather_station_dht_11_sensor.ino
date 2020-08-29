

#include <ESP8266WiFi.h>
#include <DHTesp.h>
#include "config.h"

long timeoutTime = 2000;
const int DHTPin = 14;
#define DHTpin 14    //D5 of NodeMCU is GPIO14

DHTesp dht;
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
  dht.setup(DHTpin, DHTesp::DHT11);
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
          printServerResponse();
          loadedPage = 1;
        }
      }
    }
  }

  Serial.println("Cliente desconectado");
  client.stop();  
}

void printServerResponse() {
  printResponseHeaders();
  printWeatherPage();
}

void printResponseHeaders() {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
}

void printWeatherPage() {
  client.println("<!DOCTYPE HTML>");
  client.println("<HTML>");
  printHead();
  printBody();
  client.println("</HTML>");
}

void printHead() {
  client.println("<HEAD>");
  client.println("<META CHARSET='UTF-8'>");
  client.println("<TITLE>Home Weather</TITLE>");
  client.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css'>");
  printStyleSheet();
  client.println("</HEAD>");
}

void printStyleSheet() {
  client.println("<style type='text/css'>");
  client.println("  body {background-color: #029af1; color: white; font-weight: bold}");
  client.println("  .not-available {text-decoration:line-through;}");
  client.println("  @media screen and (orientation:landscape) {");
  client.println("    .grid-container {display: grid;grid-template-columns: repeat(17, 1fr);margin: 3%;}");
  client.println("    .header {grid-area: 1 / span 18;grid-row: 1;font-size: 5vw; display:flex;justify-content: center;align-items: center;}");
  client.println("    .outdoor-icon {grid-area: 1 / span 3;grid-row: 2;font-size: 7vw;display:flex;justify-content: center;align-items: center;margin: 10% 0;}");
  client.println("    .outdoor-measurements {grid-area: 3 / span 18;font-size: 3vw;grid-row: 2;margin: 10% 0;}");
  client.println("    .outdoor-measurements-container {display: grid;grid-template-columns: repeat(14, 1fr);}");
  client.println("    .outdoor-measurement {grid-column: span 3;display:flex;justify-content: center;align-items: center;}");
  client.println("    .outdoor-weather-state {grid-column: span 2;display:flex;justify-content: center;align-items: center;}");
  client.println("    .indoor-icon {grid-area: 1 / span 3;grid-row: 3 / 5;font-size: 11vw;display:flex;justify-content: center;align-items: center;}");
  client.println("    .indoor-measurements {grid-area: 3 / span 18;grid-row: 3 / 5;font-size: 7vw;}");
  client.println("    .indoor-measurements-container {display: grid;grid-template-columns: repeat(14, 1fr);}");
  client.println("    .indoor-measurement {grid-column: span 7; grid-row: 1 / 4;display:flex;justify-content: center;align-items: center;font-size:7vw;}");
  client.println("    .indoor-sub-measurement {grid-column: span 7; grid-row: 5 / 6;display:flex;justify-content: center;align-items: center;font-size:2vw;}");

  client.println("  }");
  client.println("  @media screen and (orientation:portrait) {");
  client.println("    .grid-container {display: grid;grid-template-columns: repeat(17, 1fr);margin: 3%;}");
  client.println("    .header {grid-area: 1 / span 18;grid-row: 1;font-size: 5vw; display:flex;justify-content: center;align-items: center;}");
  client.println("    .outdoor-icon {grid-area: 1 / span 18;grid-row: 2;font-size: 7vw;display:flex;justify-content: center;align-items: center;margin: 5% 0;}");
  client.println("    .outdoor-measurements {grid-area: 1 / span 18;font-size: 3vw;grid-row: 3;margin: 5% 0;}");
  client.println("    .outdoor-measurements-container {display: grid;grid-template-columns: repeat(18, 1fr);}");
  client.println("    .outdoor-measurement {grid-column: span 4;display:flex;justify-content: center;align-items: center;}");
  client.println("    .outdoor-weather-state {grid-column: span 2;display:flex;justify-content: center;align-items: center;}");
  client.println("    .text-type-outdoor:before {margin-left: 35px;content: 'Mediciones exteriores';font-size: 3vw;}");
  client.println("    .indoor-icon {grid-area: 1 / span 18;grid-row: 4 / 6;font-size: 11vw;display:flex;justify-content: center;align-items: center;margin: 5% 0;}");
  client.println("    .indoor-measurements {grid-area: 1 / span 18;grid-row: 6 / 8;font-size: 7vw;margin: 5% 0;}");
  client.println("    .indoor-measurements-container {display: grid;grid-template-columns: repeat(18, 1fr);}");
  client.println("    .indoor-measurement {grid-column: span 9; grid-row: 1 / 4;display:flex;justify-content: center;align-items: center;font-size:7vw;}");
  client.println("    .indoor-sub-measurement {grid-column: span 9; grid-row: 5 / 6;display:flex;justify-content: center;align-items: center;font-size:2vw;}");
  client.println("    .text-type-indoor:before {margin-left: 35px;content: 'Mediciones interiores';font-size: 5vw;}");
  client.println("  }");
  client.println("</style>");
}

void printBody() {
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);
  double dewPoint = calculateDewPoint(temperature, humidity);
  client.println("<body>");
  client.println("  <div class='grid-container'>");
  client.println("    <div class='header cell-position'>Cuarto de estar</div>");

  client.println("    <div class='outdoor-icon'>");
  client.println("      <svg width='1em' height='1em' viewBox='0 0 16 16' class='bi bi-image-alt text-type-outdoor' fill='currentColor' xmlns='http://www.w3.org/2000/svg'><path d='M10.648 6.646a.5.5 0 0 1 .577-.093l4.777 3.947V15a1 1 0 0 1-1 1h-14a1 1 0 0 1-1-1v-2l3.646-4.354a.5.5 0 0 1 .63-.062l2.66 2.773 3.71-4.71z'/><path fill-rule='evenodd' d='M4.5 5a2.5 2.5 0 1 0 0-5 2.5 2.5 0 0 0 0 5z'/></svg><span class='text-type-outdoor'></span>");
  client.println("    </div>");

  client.println("    <div class='outdoor-measurements'>");
  client.println("      <div class='outdoor-measurements-container'>");
  client.println("        <div class='outdoor-measurement not-available'>");
  client.println("          <svg width='1em' height='1em' viewBox='0 0 16 16' class='bi bi-thermometer-half' fill='currentColor' xmlns='http://www.w3.org/2000/svg'><path fill-rule='evenodd' d='M6 2a2 2 0 1 1 4 0v7.627a3.5 3.5 0 1 1-4 0V2zm2-1a1 1 0 0 0-1 1v7.901a.5.5 0 0 1-.25.433A2.499 2.499 0 0 0 8 15a2.5 2.5 0 0 0 1.25-4.666.5.5 0 0 1-.25-.433V2a1 1 0 0 0-1-1z'/><path d='M9.5 12.5a1.5 1.5 0 1 1-3 0 1.5 1.5 0 0 1 3 0z'/><path fill-rule='evenodd' d='M8 1.75a.25.25 0 0 1 .25.25v10a.25.25 0 1 1-.5 0V2A.25.25 0 0 1 8 1.75z'/></svg>&nbsp;");
  client.println("          <span>32º</span>");
  client.println("        </div>");
  client.println("        <div class='outdoor-measurement not-available'>");
  client.println("          <svg width='1em' height='1em' viewBox='0 0 16 16' class='bi bi-droplet-fill' fill='currentColor' xmlns='http://www.w3.org/2000/svg'><path fill-rule='evenodd' d='M8 16a6 6 0 0 0 6-6c0-1.655-1.122-2.904-2.432-4.362C10.254 4.176 8.75 2.503 8 0c0 0-6 5.686-6 10a6 6 0 0 0 6 6zM6.646 4.646c-.376.377-1.272 1.489-2.093 3.13l.894.448c.78-1.559 1.616-2.58 1.907-2.87l-.708-.708z'/></svg>&nbsp;");
  client.println("          <span>87%</span>");
  client.println("        </div>");
  client.println("        <div class='outdoor-weather-state not-available'>");
  client.println("          <svg width='1em' height='1em' viewBox='0 0 16 16' class='bi bi-brightness-high-fill' fill='currentColor' xmlns='http://www.w3.org/2000/svg'><path d='M12 8a4 4 0 1 1-8 0 4 4 0 0 1 8 0z'/><path fill-rule='evenodd' d='M8 0a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-1 0v-2A.5.5 0 0 1 8 0zm0 13a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-1 0v-2A.5.5 0 0 1 8 13zm8-5a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1 0-1h2a.5.5 0 0 1 .5.5zM3 8a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1 0-1h2A.5.5 0 0 1 3 8zm10.657-5.657a.5.5 0 0 1 0 .707l-1.414 1.415a.5.5 0 1 1-.707-.708l1.414-1.414a.5.5 0 0 1 .707 0zm-9.193 9.193a.5.5 0 0 1 0 .707L3.05 13.657a.5.5 0 0 1-.707-.707l1.414-1.414a.5.5 0 0 1 .707 0zm9.193 2.121a.5.5 0 0 1-.707 0l-1.414-1.414a.5.5 0 0 1 .707-.707l1.414 1.414a.5.5 0 0 1 0 .707zM4.464 4.465a.5.5 0 0 1-.707 0L2.343 3.05a.5.5 0 1 1 .707-.707l1.414 1.414a.5.5 0 0 1 0 .708z'/></svg>");
  client.println("        </div>");
  client.println("        <div class='outdoor-measurement not-available'>");
  client.println("          <svg width='1em' height='1em' viewBox='0 0 16 16' class='bi bi-brightness-alt-high-fill' fill='currentColor' xmlns='http://www.w3.org/2000/svg'><path fill-rule='evenodd' d='M4 11a4 4 0 1 1 8 0 .5.5 0 0 1-.5.5h-7A.5.5 0 0 1 4 11zm4-8a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-1 0v-2A.5.5 0 0 1 8 3zm8 8a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1 0-1h2a.5.5 0 0 1 .5.5zM3 11a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1 0-1h2a.5.5 0 0 1 .5.5zm10.657-5.657a.5.5 0 0 1 0 .707l-1.414 1.414a.5.5 0 1 1-.707-.707l1.414-1.414a.5.5 0 0 1 .707 0zM4.464 7.464a.5.5 0 0 1-.707 0L2.343 6.05a.5.5 0 0 1 .707-.707l1.414 1.414a.5.5 0 0 1 0 .707z'/></svg>&nbsp;");
  client.println("          <span>6:37h</span>");
  client.println("        </div>");
  client.println("        <div class='outdoor-measurement not-available'");
  client.println("          <svg width='1em' height='1em' viewBox='0 0 16 16' class='bi bi-brightness-alt-high' fill='currentColor' xmlns='http://www.w3.org/2000/svg'><path fill-rule='evenodd' d='M5.041 10.5h5.918a3 3 0 0 0-5.918 0zM4 11a4 4 0 1 1 8 0 .5.5 0 0 1-.5.5h-7A.5.5 0 0 1 4 11zm4-8a.5.5 0 0 1 .5.5v2a.5.5 0 0 1-1 0v-2A.5.5 0 0 1 8 3zm8 8a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1 0-1h2a.5.5 0 0 1 .5.5zM3 11a.5.5 0 0 1-.5.5h-2a.5.5 0 0 1 0-1h2a.5.5 0 0 1 .5.5zm10.657-5.657a.5.5 0 0 1 0 .707l-1.414 1.414a.5.5 0 1 1-.707-.707l1.414-1.414a.5.5 0 0 1 .707 0zM4.464 7.464a.5.5 0 0 1-.707 0L2.343 6.05a.5.5 0 0 1 .707-.707l1.414 1.414a.5.5 0 0 1 0 .707z'/></svg>&nbsp;");
  client.println("          <span>21:49h</span>");
  client.println("        </div>");
  client.println("      </div>");
  client.println("    </div>");

  client.println("    <div class='indoor-icon'>");
  client.println("      <svg width='1em' height='1em' viewBox='0 0 16 16' class='bi bi-house-fill text-type-indoor' fill='currentColor' xmlns='http://www.w3.org/2000/svg'><path fill-rule='evenodd' d='M8 3.293l6 6V13.5a1.5 1.5 0 0 1-1.5 1.5h-9A1.5 1.5 0 0 1 2 13.5V9.293l6-6zm5-.793V6l-2-2V2.5a.5.5 0 0 1 .5-.5h1a.5.5 0 0 1 .5.5z'/><path fill-rule='evenodd' d='M7.293 1.5a1 1 0 0 1 1.414 0l6.647 6.646a.5.5 0 0 1-.708.708L8 2.207 1.354 8.854a.5.5 0 1 1-.708-.708L7.293 1.5z'/></svg>");
  client.println("      <span class='text-type-indoor'></span>");
  client.println("    </div>");

  client.println("    <div class='indoor-measurements'>");
  client.println("      <div class='indoor-measurements-container'>");
  client.println("        <div class='indoor-measurement'>");
  client.println("          <svg width='1em' height='1em' viewBox='0 0 16 16' class='bi bi-thermometer-half' fill='currentColor' xmlns='http://www.w3.org/2000/svg'><path fill-rule='evenodd' d='M6 2a2 2 0 1 1 4 0v7.627a3.5 3.5 0 1 1-4 0V2zm2-1a1 1 0 0 0-1 1v7.901a.5.5 0 0 1-.25.433A2.499 2.499 0 0 0 8 15a2.5 2.5 0 0 0 1.25-4.666.5.5 0 0 1-.25-.433V2a1 1 0 0 0-1-1z'/><path d='M9.5 12.5a1.5 1.5 0 1 1-3 0 1.5 1.5 0 0 1 3 0z'/><path fill-rule='evenodd' d='M8 1.75a.25.25 0 0 1 .25.25v10a.25.25 0 1 1-.5 0V2A.25.25 0 0 1 8 1.75z'/></svg>&nbsp;");
  client.print("            <span>");
  client.print(temperature);
  client.print(" ºC");
  client.println("          </span>");
  client.println("        </div>");
  client.println("        <div class='indoor-sub-measurement'>");
  client.print("            <span>Sensación térmica: ");
  client.print(heatIndex);
  client.print(" ºC");
  client.println("          </span>");
  client.println("        </div>");
  client.println("        <div class='indoor-measurement'>");
  client.println("          <svg width='1em' height='1em' viewBox='0 0 16 16' class='bi bi-droplet-fill' fill='currentColor' xmlns='http://www.w3.org/2000/svg'><path fill-rule='evenodd' d='M8 16a6 6 0 0 0 6-6c0-1.655-1.122-2.904-2.432-4.362C10.254 4.176 8.75 2.503 8 0c0 0-6 5.686-6 10a6 6 0 0 0 6 6zM6.646 4.646c-.376.377-1.272 1.489-2.093 3.13l.894.448c.78-1.559 1.616-2.58 1.907-2.87l-.708-.708z'/></svg>&nbsp;");
  client.print("            <span>");
  client.print(humidity, 0);
  client.print(" %");
  client.println("          </span>");
  client.println("        </div>");
  client.println("        <div class='indoor-sub-measurement'>");
  client.print("            <span>Punto de Rocío: ");
  client.print(dewPoint);
  client.print(" ºC");
  client.println("          </span>");
  client.println("        </div>");
  client.println("      </div>");
  client.println("    </div>");

  client.println("  </div>");
  client.println("</body>");
}

void printWifiConnectionDetails() {
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

//https://es.wikipedia.org/wiki/Punto_de_roc%C3%ADo#:~:text=Para%20una%20masa%20dada%20de,y%20se%20expresa%20en%20porcentaje.
double calculateDewPoint(float T, float H) {
  return pow((H / 100), (1.0 / 8)) * (112 + 0.9 * T) + (0.1 * T) - 112;
}
