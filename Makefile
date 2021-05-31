#!make
include .env
export


build:
	arduino-cli compile --fqbn ${ROWER_BOARD_NAME} --build-property "compiler.cpp.extra_flags=-DROWER_SSID=\"${ROWER_SSID}\" -DROWER_PASSWORD=\"${ROWER_PASSWORD}\"" ./rower

upload_spiffs:
	mkspiffs -c ./data -b 4096 -p 256 -s 0x170000 /tmp/out.spiffs
	esptool.py --chip esp32 --baud 460800 --port ${ROWER_PORT} --before default_reset --after hard_reset write_flash 0x290000 /tmp/out.spiffs

upload: build
	arduino-cli upload --fqbn ${ROWER_BOARD_NAME} --port ${ROWER_PORT} ./rower

test:
	cmake --build build && build/rower_test

screen:
	screen ${ROWER_PORT}


.PHONY: build upload test screen


