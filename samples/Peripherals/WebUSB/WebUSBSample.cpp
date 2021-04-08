#include "WebUSBSample.h"
#include "STM32WebUSB.h"

using namespace codal;

void WebUSBSample_main()
{
    STM32IotNode iotNode;
    STM32WebUSB webusb;

    printf("\n");
    printf("*******************************************\n\r");
    printf("* Demonstration de l'activation du WebUSB *\n\r");
    printf("*******************************************\n\r");

    webusb.init();

    bool state = false;
    while (true) {
        iotNode.io.led1.setDigitalValue((int)state);
        iotNode.io.led2.setDigitalValue((int)!state);
        codal::STM32IotNode::sleep(250);
        state = !state;
    }

    webusb.deInit();
}