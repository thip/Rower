#include <WiFi.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include "lib/rower.h"
#include "lib/webPresenter.h"

int pulse;
int lastPulse;
volatile bool pulsed;

const char* ssid = ROWER_SSID;
const char* password = ROWER_PASSWORD;

WebPresenter presenter;

RowerConfig config = {
    .pulseRatio = 4.805f,
    .presenter = &presenter
};

Rower rower = Rower(config);

AsyncWebServer server(80);

void IRAM_ATTR isr() {  
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
        AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/index.html");
        request->send(response);
    });

    server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
        String JSON = "{";
        JSON += "\"distance\":" + String(presenter.distance) + ",";
        JSON += "\"velocity\":" + String(presenter.velocity);
        JSON += "}";
        request->send(200, "application/json", JSON);
    });

    server.begin();

    pulse = millis();
    attachInterrupt(21, isr, RISING);
}

void loop() {
    if (pulsed){
        detachInterrupt(21);
        lastPulse = pulse;
        pulse = millis();
        
        if (pulse-lastPulse > 25){
            rower.AddPulse(pulse);
        }
        
        pulsed = false;
        attachInterrupt(21, isr, RISING);
    }
}
