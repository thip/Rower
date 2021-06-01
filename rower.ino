#include <WiFi.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include "src/rower.h"
#include "src/jsonPresenter.h"


#define SENSOR_PIN 21
#define DEBOUNCE_THRESHOLD 25
#define SERIAL_BAUD 115200
#define ROWER_PULSE_RATIO 4.805f

int pulse;
int lastPulse;
volatile bool pulsed;

AsyncWebServer server(80);
JsonPresenter presenter;
RowerConfig config = {
    .pulseRatio = ROWER_PULSE_RATIO
};
Rower rower = Rower(config);

void startSpiffs(){
    if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
}

void startWifi(){
    WiFi.begin(ROWER_SSID, ROWER_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println(WiFi.localIP());
}

void startMDNS(){
    if(!MDNS.begin("rower")) {
        Serial.println("Error starting mDNS");
        return;
    }
}

void startServer(){
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/index.html");
        request->send(response);
    });

    server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
        rower.Update(&presenter);
        presenter.Present([request](char* json){
            request->send(200, "application/json", json);
        });
    });

    server.begin();
}

void IRAM_ATTR isr() {  
  pulsed = true;
}

void setup() {
    Serial.begin(115200);
    pinMode(SENSOR_PIN, INPUT_PULLUP);

    startSpiffs();
    startWifi();
    startMDNS();
    startServer();

    pulse = millis();
    attachInterrupt(SENSOR_PIN, isr, RISING);
}

void loop() {
    if (pulsed){
        detachInterrupt(SENSOR_PIN);
        lastPulse = pulse;
        pulse = millis();
        
        if (pulse-lastPulse > DEBOUNCE_THRESHOLD){
            rower.AddPulse(pulse);
        }
        
        pulsed = false;
        attachInterrupt(SENSOR_PIN, isr, RISING);
    }
}


