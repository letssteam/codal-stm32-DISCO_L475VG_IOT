#include "STM32IotNode.h"

#ifndef TIMER_SAMPLE_H
#define TIMER_SAMPLE_H

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN TimerSample_main
#endif

/*
  Timebase callback
  This example shows how to configure HardwareTimer to execute a callback at regular interval.
  Callback toggles pin.
  Once configured, there is only CPU load for callbacks executions.
*/

void TimerSample_main();

#endif