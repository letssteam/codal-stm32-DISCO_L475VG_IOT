#include "WebUSBSample.h"

#include <cstdio>

#include "STM32WebUSB.h"

void WebUSBSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    codal::STM32WebUSB webusb;

    webusb.init();

    // We block execution Serial USB is not connected
    while (!webusb.isConnected()) {
    }

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("* Demonstration de l'activation du WebUSB *\r\n");
    printf("*******************************************\r\n");

    bool state = false;
    while (true) {
        discoL475VgIot.io.led1.setDigitalValue((int)state);
        discoL475VgIot.io.led2.setDigitalValue((int)!state);

        webusb.send(".");

        while (webusb.isReadable() > 0) {
            webusb.send((char)webusb.getChar(codal::ASYNC));
        }

        discoL475VgIot.sleep(1000);
        state = !state;
    }
}
