#pragma once

#include "LPS22HB.h"
#include "STM32DISCO_L475VG_IOT.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN lps22hbSample
#endif

void lps22hbSample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot);
