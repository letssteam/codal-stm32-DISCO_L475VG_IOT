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
#elif defined(OLED_SSD1306_SAMPLE)
#include "OLED_SSD1306.h"
#elif defined(HTS221_SAMPLE)
#include "HTS221_sample.h"
#else
#include "BlinkSample.h"
#endif

using namespace codal;

int main() {
    SAMPLE_MAIN();
    release_fiber();
}