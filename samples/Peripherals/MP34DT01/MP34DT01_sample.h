
#ifndef __HTS221_SAMPLE_H__
#define __HTS221_SAMPLE_H__

#include "MP34DT01.h"
#include "STM32DISCO_L475VG_IOT.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN mp32dt01Sample
#endif

void mp32dt01Sample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot);

#endif
