
#include "CodalFiber.h"
#include "STM32DISCO_L475VG_IOT.h"

#if defined(GPIO_SAMPLE)
#include "GPIOSample.h"
#elif defined(ADC_SAMPLE)
#include "ADCSample.h"
#elif defined(SERIAL_SAMPLE)
#include "SerialSample.h"
#elif defined(PIN_SAMPLE)
#include "PinSample.h"
#else
#include "BlinkSample.h"
#endif

codal::STM32DISCO_L475VG_IOT discoL475VgIot;

int main()
{
    discoL475VgIot.init();
    SAMPLE_MAIN(discoL475VgIot);
    codal::release_fiber();
    return 0;
}
