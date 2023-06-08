
#include "MP34DT01_sample.h"

#include <cstdio>
#include <string>

codal::MP34DT01 micro;

void mp32dt01Sample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*        Demonstration du MP32DT01        *\r\n");
    printf("*******************************************\r\n");

    printf("Init. microphone...");
    discoL475VgIot.sleep(1000);

    if (!micro.init()) {
        printf("FAIL\r\n");
    }
    printf("Ok\r\n");

    while (true) {
        printf("Measured: %ddB\n", micro.getDecibel());
        discoL475VgIot.sleep(500);
    }
}
