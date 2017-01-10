#!/bin/bash

chip=at90usb82

sudo dfu-programmer ${chip} erase
sudo dfu-programmer ${chip} flash usbserial_uno_8u2.hex
sudo dfu-programmer ${chip} reset
