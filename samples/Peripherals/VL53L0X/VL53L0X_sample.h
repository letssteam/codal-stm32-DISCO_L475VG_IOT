
#ifndef __HTS221_SAMPLE_H__
#define __HTS221_SAMPLE_H__

#include "STM32DISCO_L475VG_IOT.h"
#include "VL53L0X.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN vlx53l0xSample
#endif

void vlx53l0xSample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot);

#endif
