#pragma once

#include "HTS221.h"
#include "STM32DISCO_L475VG_IOT.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN hts221Sample
#endif

void hts221Sample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot);
