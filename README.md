# Rower
Custom ESP32 based monitor for the WaterRower A1 🚣

[![Tests](https://github.com/thip/Rower/actions/workflows/Tests.yml/badge.svg)](https://github.com/thip/Rower/actions/workflows/Tests.yml)

## Features
- [x] Web based interface displaying:
  - [x] Distance
  - [x] 500m pace
  - [x] Stroke Acceleration
- [ ] More soon!
## Hardware
- [WaterRower A1 rowing machine](https://www.waterrower.co.uk/waterrower-a1-studio-rowing-machine)
- [Adafruit HUZZAH32 – ESP32 Feather Board](https://www.adafruit.com/product/3405)
- 2 pin female JST-SM connector and wires to connect to WaterRower sensor

## Prerequisites
- [arduino-cli](https://github.com/arduino/arduino-cli) with esp32 core installed
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) library installed
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) installed

## Getting Started
1. Connect your ESP32 board via USB 
1. Create a file called `.env` in the root folder of your local copy of this repo
1. Populate `.env` with your specific config (use `.env.example` as a guide)
1. Run `make`
1. Connect your ESP32 to your WaterRower A1 sensor - the positive lead goes to pin 21, the other goes to gnd (use a multimeter to work out which is which) 
1. Power up the ESP32 and switch on the A1 monitor (We're just using it to provide power to the sensor for now)
1. Browse to http://rower.local/
1. Start Rowing!

