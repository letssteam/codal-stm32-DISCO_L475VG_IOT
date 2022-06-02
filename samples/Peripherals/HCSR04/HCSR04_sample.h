#pragma once

#include "HCSR04.h"
#include "HCSR04Sensor.h"
#include "STM32DISCO_L475VG_IOT.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN hcsr04Sample
#endif

void hcsr04Sample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot);
