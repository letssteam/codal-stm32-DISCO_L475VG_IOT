#!/bin/sh
set -e
./build.py
openocd -s "/usr/share/openocd/scripts/" -s"libraries/codal-stm32-iot-node/scripts/" -f "openocd.cfg" -c "program STM32_IOT_NODE.hex verify reset exit "
