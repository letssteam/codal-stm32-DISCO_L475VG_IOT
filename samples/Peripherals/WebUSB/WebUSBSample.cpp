#include "WebUSBSample.h"

#include "STM32WebUSB.h"

using namespace codal;

void WebUSBSample_main()
{
    STM32IotNode iotNode;
    STM32WebUSB webusb;

    webusb.init();

    // We block execution Serial USB is not connected
    while (!webusb.isConnected()) {
    }

    printf("\n");
    printf("*******************************************\n\r");
    printf("* Demonstration de l'activation du WebUSB *\n\r");
    printf("*******************************************\n\r");

    bool state = false;
    while (true) {
        iotNode.io.led1.setDigitalValue((int)state);
        iotNode.io.led2.setDigitalValue((int)!state);

        webusb.send(".");

        while (webusb.isReadable() > 0) {
            webusb.send((char)webusb.getChar(ASYNC));
        }

        codal::STM32IotNode::sleep(1000);
        state = !state;
    }
}