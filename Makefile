#!make
include .env
export


all: test build upload upload_spiffs

build:
	arduino-cli compile --fqbn ${ROWER_BOARD_NAME} --build-property "compiler.cpp.extra_flags=-DROWER_SSID=\"${ROWER_SSID}\" -DROWER_PASSWORD=\"${ROWER_PASSWORD}\"" ./rower

build_web:
	cd web && npm run build

upload_spiffs: build_web
	${MKSPIFFS} -c ./web/build -b 4096 -p 256 -s 0x170000 /tmp/out.spiffs
	${ESPTOOL} --chip esp32 --baud 460800 --port ${ROWER_PORT} --before default_reset --after hard_reset write_flash 0x290000 /tmp/out.spiffs

upload: build
	arduino-cli upload --fqbn ${ROWER_BOARD_NAME} --port ${ROWER_PORT} ./rower

test: build_tests
	 build/rower_test

screen:
	screen ${ROWER_PORT} 115200


build_tests:
	cmake -B build && cmake --build build


.PHONY: build build_web upload test build_tests screen


