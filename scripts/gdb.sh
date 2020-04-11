#!/bin/sh
arm-none-eabi-gdb --eval "target remote | openocd -s /usr/share/openocd/scripts/ -s libraries/codal-stm32-iot-node/scripts/ -f openocd.cfg -f debug.cfg" build/STM32_IOT_NODE
