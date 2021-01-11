#!/bin/sh
set -e
./build.py
openocd -s "/usr/share/openocd/scripts/" -s"libraries/codal-stm32-DISCO_L475VG_IOT/scripts/" -f "openocd.cfg" -c "program DISCO_L475VG_IOT.hex verify reset exit "
