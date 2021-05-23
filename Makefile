build:
	arduino-cli compile --fqbn esp32:esp32:featheresp32 ./rower

upload:
	arduino-cli upload --fqbn esp32:esp32:featheresp32 --port /dev/cu.SLAB_USBtoUART ./rower

test:
	cmake --build build && build/rower_test


.PHONY: build upload test