#include "STM32IotNode.h"

#if defined(GPIO_SAMPLE)
#include "GPIOSample.h"
#elif defined(ADC_SAMPLE)
#include "ADCSample.h"
#elif defined(SERIAL_SAMPLE)
#include "SerialSample.h"
#elif defined(TIMER_SAMPLE)
#include "TimerSample.h"
#elif defined(HADWARE_TIMER_SAMPLE)
#include "HardwareTimerSample.h"
#else
#include "BlinkSample.h"
#endif

using namespace codal;

int main() {
    SAMPLE_MAIN();
    release_fiber();
}