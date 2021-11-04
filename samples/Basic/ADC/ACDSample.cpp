#include <cstdio>

#include "ADCSample.h"

using namespace codal;

void ADCSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\n");
    printf("*******************************************\r\n");
    printf("*               ADC Example               *\r\n");
    printf("*******************************************\r\n");

    while (true) {
        discoL475VgIot.serial.printf("ADC Value : %d\r\n", discoL475VgIot.io.A0.getAnalogValue());
        discoL475VgIot.sleep(1000);
    }
}
