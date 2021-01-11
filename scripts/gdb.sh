#!/bin/sh
arm-none-eabi-gdb --eval "target remote | openocd -s /usr/share/openocd/scripts/ -s libraries/codal-stm32-DISCO_L475VG_IOT/scripts/ -f openocd.cfg -f debug.cfg" build/DISCO_L475VG_IOT
