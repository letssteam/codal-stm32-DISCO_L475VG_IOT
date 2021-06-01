#include "BLE_Serial_Sample.h"

#include "STM32SerialBLE.h"

using namespace codal;
using namespace std;

STM32IotNode iotNode;

HCISpiTransportClass hci(iotNode.spi3, SPBTLE_RF, pinNametoDigitalPin(PD_13), pinNametoDigitalPin(PE_6),
                         pinNametoDigitalPin(PA_8), 8000000, 0);
BLELocalDevice objBLE(&hci);
BLELocalDevice& BLE = objBLE;

void blePeripheralConnectHandler(BLEDevice central)
{
    printf("BLE Connected : %s\n\r", central.address().c_str());
}

void blePeripheralDisconnectHandler(BLEDevice central)
{
    printf("BLE Disconnected : %s\n\r", central.address().c_str());
}

void BLE_Serial_Sample_main()
{
    iotNode.serial.init(115200);

    printf("\n\r");
    printf("*******************************************\n\r");
    printf("*       Demonstration du Serial BLE       *\n\r");
    printf("*******************************************\n\r");

    bool state = false;

    if (BLE.begin()) {
        printf("BLE Initialized !\n\r");
    }
    else {
        printf("Failed to initialize BLE !!\n\r");

        while (true) {
            iotNode.io.led2.setDigitalValue(state ? 1 : 0);
            iotNode.io.led1.setDigitalValue(state ? 0 : 1);
            state = !state;
            codal::STM32IotNode::sleep(50);
        }
    }

    STM32SerialBLE bleSerial("6E400001-B5A3-F393-E0A9-E50E24DCCA9E", "6E400002-B5A3-F393-E0A9-E50E24DCCA9E",
                             "6E400003-B5A3-F393-E0A9-E50E24DCCA9E");

    BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
    BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
    BLE.setLocalName("IoT-Node BLE");
    BLE.setAdvertisedService(bleSerial.getService());
    BLE.advertise();

    while (true) {
        iotNode.io.led1.setDigitalValue(state ? 1 : 0);
        iotNode.io.led2.setDigitalValue(state ? 0 : 1);

        if (bleSerial.available() > 0) {
            bleSerial.send("Recv " + to_string(bleSerial.available()) + " bytes");
            printf("Recv: %s\n\r", bleSerial.read().c_str());
        }

        iotNode.sleep(150);
        state = !state;
        BLE.poll();
    }
}