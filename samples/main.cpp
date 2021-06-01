#include "STM32IotNode.h"

#if defined(GPIO_SAMPLE)
#include "GPIOSample.h"
#elif defined(ADC_SAMPLE)
#include "ADCSample.h"
#elif defined(SERIAL_SAMPLE)
#include "SerialSample.h"
#elif defined(SERIALUSB_SAMPLE)
#include "SerialUSBSample.h"
#elif defined(SPI_SAMPLE)
#include "SpiSample.h"
#elif defined(TIMER_SAMPLE)
#include "TimerSample.h"
#elif defined(WEBUSB_SAMPLE)
#include "WebUSBSample.h"
#elif defined(BLE_PERIPHERAL_SAMPLE)
#include "BLE_Peripheral_Sample.h"
#elif defined(BLE_SERIAL_SAMPLE)
#include "BLE_Serial_Sample.h"
#elif defined(HADWARE_TIMER_SAMPLE)
#include "HardwareTimerSample.h"
#elif defined(OLED_SSD1306_SAMPLE)
#include "OLED_SSD1306.h"
#elif defined(HTS221_SAMPLE)
#include "HTS221_sample.h"
#elif defined(LPS22HB_SAMPLE)
#include "LPS22HB_sample.h"
#elif defined(VL53L0X_SAMPLE)
#include "VL53L0X_sample.h"
#elif defined(LIS3MDL_SAMPLE)
#include "LIS3MDL_sample.h"
#elif defined(LSM6DSL_SAMPLE)
#include "LSM6DSL_sample.h"
#elif defined(LSM6DSL_ACCEL_EVENT_SAMPLE)
#include "LSM6DSL_accel_sample_event.h"
#else
#include "BlinkSample.h"
#endif

using namespace codal;

int main()
{
    SAMPLE_MAIN();
    release_fiber();
}