#pragma once

#include "STM32DISCO_L475VG_IOT.h"
#include "openlog.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN openLogSample
#endif

void openLogSample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot);
