#include "SerialUSBSample.h"

#include "STM32USBSerial.h"

using namespace codal;
using namespace std;

void SerialUSBSample_main()
{
    STM32IotNode iotnode;
    STM32USBSerial usbSerial;

    usbSerial.init();

    // We block execution Serial USB is not connected
    while (!usbSerial.isConnected()) {
    }

    usbSerial.send("\n\r");
    usbSerial.send("*******************************************\n\r");
    usbSerial.send("* Demonstration de la communication serie *\n\r");
    usbSerial.send("*******************************************\n\r");

    bool state = false;

    while (true) {
        iotnode.io.led1.setDigitalValue((int)state);
        iotnode.io.led2.setDigitalValue((int)state);
        usbSerial.send(".");

        while (usbSerial.isReadable() > 0) {
            usbSerial.send(usbSerial.getChar(ASYNC));
        }

        codal::STM32IotNode::sleep(1000);
        state = !state;
    }
}
