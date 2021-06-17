#pragma once

#include "STM32DISCO_L475VG_IOT.h"
#include "ssd1306.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN OledSample_main
#endif

void OledSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot);
