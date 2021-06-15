
#ifndef __HTS221_SAMPLE_H__
#define __HTS221_SAMPLE_H__

#include "HTS221.h"
#include "STM32DISCO_L475VG_IOT.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN hts221Sample
#endif

void hts221Sample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot);

#endif
