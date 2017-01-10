#!/bin/bash

chip=at90usb82

sudo dfu-programmer ${chip} erase
sudo dfu-programmer ${chip} flash arduino_midi.hex
sudo dfu-programmer ${chip} reset
