#include "LIS3MDL_sample.h"

#include <cstdio>

void lis3mdlSample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*         Demonstration du LIS3MDL        *\r\n");
    printf("*******************************************\r\n");

    codal::LIS3MDL lis3mdl(&discoL475VgIot.i2c2, 0x3C);
    lis3mdl.init();

    while (true) {
        auto values = lis3mdl.getMeasure();

        printf("X : %5u mGauss\tY : %5u mGauss\tZ : %5u mGauss\r\n", values[0], values[1], values[2]);
        printf("\r\n");

        discoL475VgIot.sleep(1000);
    }
}
