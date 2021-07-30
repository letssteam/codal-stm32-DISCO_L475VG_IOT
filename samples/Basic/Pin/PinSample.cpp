#include "PinSample.h"

#include "STM32DISCO_L475VG_IOT_IO.h"
#include "STM32Pin.h"

using codal::STM32Pin;

void PinSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    STM32Pin& led1 = discoL475VgIot.io.led1;
    STM32Pin& led2 = discoL475VgIot.io.led2;

    while (true) {
        led1.setDigitalValue(1);
        led2.setDigitalValue(0);
        discoL475VgIot.sleep(1000);
        led1.setDigitalValue(0);
        led2.setDigitalValue(1);
        discoL475VgIot.sleep(1000);
    }
}
