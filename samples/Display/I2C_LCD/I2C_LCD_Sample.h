#pragma once

#include "STM32DISCO_L475VG_IOT.h"
#include "i2c_lcd.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN i2cLCDSample_main
#endif

void i2cLCDSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot);
