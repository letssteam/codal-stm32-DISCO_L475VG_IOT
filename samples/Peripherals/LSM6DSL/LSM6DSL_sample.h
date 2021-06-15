
#ifndef __HTS221_SAMPLE_H__
#define __HTS221_SAMPLE_H__

#include "LSM6DSL.h"
#include "STM32DISCO_L475VG_IOT.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN lsm6dslSample
#endif

void lsm6dslSample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot);

#endif
