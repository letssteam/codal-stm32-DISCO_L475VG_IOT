#include "BLE_Broadcast_Sample.h"

#include "STM32duinoBLE.h"
#include "wiring_constants.h"
#include "wiring_digital.h"
#include "wiring_time.h"

using namespace codal;
using namespace std;

STM32IotNode iotNode;
HCISpiTransportClass hci(iotNode.spi3, SPBTLE_RF, pinNametoDigitalPin(PD_13), pinNametoDigitalPin(PE_6),
                         pinNametoDigitalPin(PA_8), 8000000, 0);
BLELocalDevice BLEObj(&hci);
BLELocalDevice& BLE = BLEObj;

void BLE_Broadcast_Sample_main()
{
    iotNode.serial.init(115200);

    printf("\n\r");
    printf("*******************************************\n\r");
    printf("*      Demonstration du BLE Broadcast     *\n\r");
    printf("*******************************************\n\r");

    bool state = false;

    if (BLE.begin()) {
        printf("BLE Initialized !\n\r");
    }
    else {
        printf("Failed to initialize BLE !!\n\r");

        while (true) {
            iotNode.io.led2.setDigitalValue(state ? 1 : 0);
            iotNode.io.led1.setDigitalValue(state ? 1 : 0);
            state = !state;
            codal::STM32IotNode::sleep(50);
        }
    }

    const char* advDataStr = "My broadcast message !";

    BLEAdvertisingData advData;
    advData.setAdvertisedServiceData(0x1800, (uint8_t*)advDataStr, strlen(advDataStr));

    BLE.setAdvertisingData(advData);
    BLE.setLocalName("My Device");
    BLE.setConnectable(false);
    BLE.advertise(37);

    while (true) {
        iotNode.io.led2.setDigitalValue(state ? 1 : 0);
        iotNode.io.led1.setDigitalValue(state ? 0 : 1);
        state = !state;
        codal::STM32IotNode::sleep(150);

        BLE.poll();
    }
}
