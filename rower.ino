#include <WiFi.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
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

String processor(const String& var){
  if(var == "DISTANCE"){
    String distance = String(presenter.distance);
    return distance;
  }
  if(var == "VELOCITY"){
    String velocity = String(presenter.velocity);
    return velocity;
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

    if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

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
        // request->send_P(200, "text/html", index_html, processor);
        request->send(SPIFFS, "/index.html", String(), false, processor);
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
