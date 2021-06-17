#include "SerialUSBSample.h"

#include <cstdio>

#include "STM32USBSerial.h"

void SerialUSBSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    codal::STM32USBSerial usbSerial;

    usbSerial.init();

    // We block execution Serial USB is not connected
    while (!usbSerial.isConnected()) {
    }

    usbSerial.send("\r\n");
    usbSerial.send("*******************************************\r\n");
    usbSerial.send("* Demonstration de la communication serie *\r\n");
    usbSerial.send("*******************************************\r\n");

    bool state = false;

    while (true) {
        discoL475VgIot.io.led1.setDigitalValue((int)state);
        discoL475VgIot.io.led2.setDigitalValue((int)state);
        usbSerial.send(".");

        while (usbSerial.isReadable() > 0) {
            usbSerial.send(usbSerial.getChar(codal::ASYNC));
        }

        discoL475VgIot.sleep(1000);
        state = !state;
    }
}
