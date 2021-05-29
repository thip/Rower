#include <WiFi.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "rower.h"
#include "webPresenter.h"

int pulse;
int lastPulse;
bool pulsed;

const char* ssid = ROWER_SSID;
const char* password = ROWER_PASSWORD;

WebPresenter presenter;

RowerConfig config = {
    .pulseRatio = 4.805f,
    .presenter = &presenter
};

Rower rower = Rower(config);

// Set web server port number to 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  %DISTANCEPLACEHOLDER%
</body>
</html>
)rawliteral";

String processor(const String& var){
  if(var == "DISTANCEPLACEHOLDER"){
    String distance = "Distance: " + String(presenter.distance);
    return distance;
  }
  return String();
}

void IRAM_ATTR isr() {
  lastPulse = pulse;
  int pulse = millis();
  if (pulse-lastPulse < 25){
      return;
  }
  
  pulsed = true;
}

void setup() {
    Serial.begin(115200);
    pinMode(21, INPUT_PULLUP);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }

    if(!MDNS.begin("rower")) {
        Serial.println("Error starting mDNS");
        return;
    }

    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html, processor);
    });

    server.begin();

    pulse = millis();
    attachInterrupt(21, isr, RISING);
}

void loop() {
    if (pulsed){
        detachInterrupt(21);
        rower.AddPulse(pulse);
        pulsed = false;
        attachInterrupt(21, isr, RISING);
    }
}
