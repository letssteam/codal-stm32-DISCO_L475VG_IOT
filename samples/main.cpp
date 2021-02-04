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
#elif defined(LPS22HB_SAMPLE)
#include "LPS22HB_sample.h"
#elif defined(VL53L0X_SAMPLE)
#include "VL53L0x_sample.h"
#elif defined(LIS3MDL_SAMPLE)
#include "LIS3MDL_sample.h"
#else
#include "BlinkSample.h"
#endif

using namespace codal;

int main() {
    SAMPLE_MAIN();
    release_fiber();
}