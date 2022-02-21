
#include "CodalFiber.h"
#include "STM32DISCO_L475VG_IOT.h"

#if defined(GPIO_SAMPLE)
#include "GPIOSample.h"
#elif defined(PIN_SAMPLE)
#include "PinSample.h"
#elif defined(ADC_SAMPLE)
#include "ADCSample.h"
#elif defined(PWM_SAMPLE)
#include "PWMSample.h"
#elif defined(SERIAL_SAMPLE)
#include "SerialSample.h"
#elif defined(SPI_SAMPLE)
#include "SpiSample.h"
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
#elif defined(VL53L0X_SAMPLE)
#include "VL53L0X_sample.h"
#elif defined(SERIALUSB_SAMPLE)
#include "SerialUSBSample.h"
#elif defined(WEBUSB_SAMPLE)
#include "WebUSBSample.h"
#elif defined(BLE_PERIPHERAL_SAMPLE)
#include "BLE_Peripheral_Sample.h"
#elif defined(BLE_BROADCAST_SAMPLE)
#include "BLE_Broadcast_Sample.h"
#elif defined(BLE_SCANNING_SAMPLE)
#include "BLE_Scanning_Sample.h"
#elif defined(BLE_SERIAL_SAMPLE)
#include "BLE_Serial_Sample.h"
#elif defined(OLED_SSD1306_SAMPLE)
#include "OLED_SSD1306.h"
#elif defined(WIFI_HTTP_CLIENT_SAMPLE)
#include "WIFI_Http_Client_Sample.h"
#elif defined(WIFI_BUFFER_SAMPLE)
#include "WIFI_Buffer_Sample.h"
#elif defined(MESSAGEBUS_SAMPLE)
#include "MessageBus_Sample.h"
#else
#include "BlinkSample.h"
#endif

codal::STM32DISCO_L475VG_IOT discoL475VgIot;

auto main() -> int
{
    discoL475VgIot.init();
    SAMPLE_MAIN(discoL475VgIot);
    codal::release_fiber();
    return 0;
}
