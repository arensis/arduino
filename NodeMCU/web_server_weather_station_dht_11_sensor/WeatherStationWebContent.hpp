class WeatherStationWebContent {
  public:
    WeatherStationWebContent(String roomType, float humidity, float temperature, float heatIndex) {
      this -> roomType = roomType;
      this -> humidity = humidity;
      this -> temperature = temperature;
      this -> heatIndex = heatIndex;
    }
    String getWebContent() {
      String content = "<!DOCTYPE HTML>";
      content += "<HTML>";
      content += getHeadContent();
      content += getBodyContent();
      content += "</HTML>";

      return content;
    }

  private:
    String roomType;
    float humidity;
    float temperature;
    float heatIndex;
    String getHeadContent() {
      String headContent = "<HEAD>";
      headContent += "<META CHARSET='UTF-8'>";
      headContent += "<TITLE>Home Weather</TITLE>";
      headContent += "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css'>";
      headContent += getStyleSheetContent();
      headContent += "</HEAD>";
    
      return headContent;
    }
    
    String getStyleSheetContent() {
      String styleSheetContent = "<style type='text/css'>";
      styleSheetContent += "  body {background-color: #029af1; color: white; font-weight: bold}";
      styleSheetContent += "  .not-available {text-decoration:line-through;}";
      styleSheetContent += "  @media screen and (orientation:landscape) {";
      styleSheetContent += "    .grid-container {display: grid;grid-template-columns: repeat(17, 1fr);margin: 3%;}";
      styleSheetContent += "    .header {grid-area: 1 / span 18;grid-row: 1;font-size: 5vw; display:flex;justify-content: center;align-items: center;}";

      styleSheetContent += "    .indoor-icon {grid-area: 1 / span 3;grid-row: 3 / 5;font-size: 11vw;display:flex;justify-content: center;align-items: center;}";
      styleSheetContent += "    .indoor-measurements {grid-area: 3 / span 18;grid-row: 3 / 5;font-size: 7vw;}";
      styleSheetContent += "    .indoor-measurements-container {display: grid;grid-template-columns: repeat(14, 1fr);}";
      styleSheetContent += "    .indoor-measurement {grid-column: span 7; grid-row: 1 / 4;display:flex;justify-content: center;align-items: center;font-size:7vw;}";
      styleSheetContent += "    .indoor-sub-measurement {grid-column: span 7; grid-row: 5 / 6;display:flex;justify-content: center;align-items: center;font-size:2vw;}";
      styleSheetContent += "  }";
      
      styleSheetContent += "  @media screen and (orientation:portrait) {";
      styleSheetContent += "    .grid-container {display: grid;grid-template-columns: repeat(17, 1fr);margin: 3%;}";
      styleSheetContent += "    .header {grid-area: 1 / span 18;grid-row: 1;font-size: 5vw; display:flex;justify-content: center;align-items: center;}";
      
      styleSheetContent += "    .indoor-icon {grid-area: 1 / span 18;grid-row: 4 / 6;font-size: 11vw;display:flex;justify-content: center;align-items: center;margin: 5% 0;}";
      styleSheetContent += "    .indoor-measurements {grid-area: 1 / span 18;grid-row: 6 / 8;font-size: 7vw;margin: 5% 0;}";
      styleSheetContent += "    .indoor-measurements-container {display: grid;grid-template-columns: repeat(18, 1fr);}";
      styleSheetContent += "    .indoor-measurement {grid-column: span 9; grid-row: 1 / 4;display:flex;justify-content: center;align-items: center;font-size:7vw;}";
      styleSheetContent += "    .indoor-sub-measurement {grid-column: span 9; grid-row: 5 / 6;display:flex;justify-content: center;align-items: center;font-size:2vw;}";
      styleSheetContent += "    .text-type-indoor:before {margin-left: 35px;content: 'Mediciones interiores';font-size: 5vw;}";
      styleSheetContent += "  }";
      styleSheetContent += "</style>";
    
      return styleSheetContent;
    }
    
    String getBodyContent() {
      String bodyContent = "<body>";
      bodyContent += "  <div class='grid-container'>";
      bodyContent += "    <div class='header cell-position'>";
      bodyContent += roomType;
      bodyContent += "  </div>";
  
      bodyContent += "    <div class='indoor-icon'>";
      bodyContent += "      <svg width='1em' height='1em' viewBox='0 0 16 16' class='bi bi-house-fill text-type-indoor' fill='currentColor' xmlns='http://www.w3.org/2000/svg'><path fill-rule='evenodd' d='M8 3.293l6 6V13.5a1.5 1.5 0 0 1-1.5 1.5h-9A1.5 1.5 0 0 1 2 13.5V9.293l6-6zm5-.793V6l-2-2V2.5a.5.5 0 0 1 .5-.5h1a.5.5 0 0 1 .5.5z'/><path fill-rule='evenodd' d='M7.293 1.5a1 1 0 0 1 1.414 0l6.647 6.646a.5.5 0 0 1-.708.708L8 2.207 1.354 8.854a.5.5 0 1 1-.708-.708L7.293 1.5z'/></svg>";
      bodyContent += "      <span class='text-type-indoor'></span>";
      bodyContent += "    </div>";
    
      bodyContent += "    <div class='indoor-measurements'>";
      bodyContent += "      <div class='indoor-measurements-container'>";
      bodyContent += "        <div class='indoor-measurement'>";
      bodyContent += "          <svg width='1em' height='1em' viewBox='0 0 16 16' class='bi bi-thermometer-half' fill='currentColor' xmlns='http://www.w3.org/2000/svg'><path fill-rule='evenodd' d='M6 2a2 2 0 1 1 4 0v7.627a3.5 3.5 0 1 1-4 0V2zm2-1a1 1 0 0 0-1 1v7.901a.5.5 0 0 1-.25.433A2.499 2.499 0 0 0 8 15a2.5 2.5 0 0 0 1.25-4.666.5.5 0 0 1-.25-.433V2a1 1 0 0 0-1-1z'/><path d='M9.5 12.5a1.5 1.5 0 1 1-3 0 1.5 1.5 0 0 1 3 0z'/><path fill-rule='evenodd' d='M8 1.75a.25.25 0 0 1 .25.25v10a.25.25 0 1 1-.5 0V2A.25.25 0 0 1 8 1.75z'/></svg>&nbsp;";
      bodyContent += "            <span>";
      bodyContent += temperature;
      bodyContent += " ºC";
      bodyContent += "          </span>";
      bodyContent += "        </div>";
      bodyContent += "        <div class='indoor-sub-measurement'>";
      bodyContent += "            <span>Sensación térmica: ";
      bodyContent += heatIndex;
      bodyContent += " ºC";
      bodyContent += "          </span>";
      bodyContent += "        </div>";
      bodyContent += "        <div class='indoor-measurement'>";
      bodyContent += "          <svg width='1em' height='1em' viewBox='0 0 16 16' class='bi bi-droplet-fill' fill='currentColor' xmlns='http://www.w3.org/2000/svg'><path fill-rule='evenodd' d='M8 16a6 6 0 0 0 6-6c0-1.655-1.122-2.904-2.432-4.362C10.254 4.176 8.75 2.503 8 0c0 0-6 5.686-6 10a6 6 0 0 0 6 6zM6.646 4.646c-.376.377-1.272 1.489-2.093 3.13l.894.448c.78-1.559 1.616-2.58 1.907-2.87l-.708-.708z'/></svg>&nbsp;";
      bodyContent += "            <span>";
      bodyContent += humidity;
      bodyContent += " %";
      bodyContent += "          </span>";
      bodyContent += "        </div>";
      bodyContent += "        <div class='indoor-sub-measurement'>";
      bodyContent += "            <span>Punto de Rocío: ";
      bodyContent += calculateDewPoint(temperature, humidity);
      bodyContent += " ºC";
      bodyContent += "          </span>";
      bodyContent += "        </div>";
      bodyContent += "      </div>";
      bodyContent += "    </div>";
    
      bodyContent += "  </div>";
      bodyContent += "</body>";
    
      return bodyContent;
    }
    
    //https://es.wikipedia.org/wiki/Punto_de_roc%C3%ADo#:~:text=Para%20una%20masa%20dada%20de,y%20se%20expresa%20en%20porcentaje.
    double calculateDewPoint(float T, float H) {
      return pow((H / 100), (1.0 / 8)) * (112 + 0.9 * T) + (0.1 * T) - 112;
    }
};
