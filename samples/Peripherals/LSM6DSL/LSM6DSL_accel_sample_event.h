
#ifndef __HTS221_ACCEL_SAMPLE_EVENT_H__
#define __HTS221_ACCEL_SAMPLE_EVENT_H__

#include "LSM6DSL_Accelerometer.h"
#include "STM32DISCO_L475VG_IOT.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN lsm6dslAccelEventSample
#endif

void lsm6dslAccelEventSample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot);

#endif
