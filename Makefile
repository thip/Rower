#!make
include .env
export

build:
	arduino-cli compile --fqbn esp32:esp32:featheresp32 --build-property "compiler.cpp.extra_flags=-DROWER_SSID=\"${ROWER_SSID}\" -DROWER_PASSWORD=\"${ROWER_PASSWORD}\"" ./rower

upload: build
	arduino-cli upload --fqbn esp32:esp32:featheresp32 --port /dev/cu.SLAB_USBtoUART ./rower

test:
	cmake --build build && build/rower_test


.PHONY: build upload test


