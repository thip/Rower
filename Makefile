#!make
include .env
export


build:
	arduino-cli compile --fqbn esp32:esp32:featheresp32 --build-property "compiler.cpp.extra_flags=-DROWER_SSID=\"${ROWER_SSID}\" -DROWER_PASSWORD=\"${ROWER_PASSWORD}\"" ./rower

upload_spiffs:
	mkspiffs -c ./data -b 4096 -p 256 -s 0x170000 /tmp/out.spiffs
	esptool.py --chip esp32 --baud 460800 --port /dev/cu.SLAB_USBtoUART --before default_reset --after hard_reset write_flash 0x290000 /tmp/out.spiffs

upload: build
	arduino-cli upload --fqbn esp32:esp32:featheresp32 --port /dev/cu.SLAB_USBtoUART ./rower

test:
	cmake --build build && build/rower_test


.PHONY: build upload test


