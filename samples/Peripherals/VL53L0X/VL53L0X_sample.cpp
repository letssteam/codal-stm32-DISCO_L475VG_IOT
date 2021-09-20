
#include "VL53L0X_sample.h"

#include <cstdio>
#include <string>

void vlx53l0xSample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*         Demonstration du VL53L0X        *\r\n");
    printf("*******************************************\r\n");

    codal::VL53L0X vl53l0x(&discoL475VgIot.i2c2, &discoL475VgIot.io.pc6, 0x52);

    vl53l0x.init();

    discoL475VgIot.sleep(2000);

    std::string distance;

    while (true) {
        distance = "Distance : " + std::to_string(vl53l0x.getDistance()) + " mm";

        printf("%s \r\n", distance.c_str());
        printf("\r\n");

        discoL475VgIot.sleep(500);
    }
}
