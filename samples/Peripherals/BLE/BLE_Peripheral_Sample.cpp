#include "BLE_Peripheral_Sample.h"

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

void BLE_HCI_Sample_main()
{
    BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");
    BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

    iotNode.serial.init(115200);

    printf("\n\r");
    printf("*******************************************\n\r");
    printf("*  Demonstration du Bluetooth Low Energy  *\n\r");
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
            codal::STM32IotNode::sleep(100);
        }
    }

    // set advertised local name and service UUID:
    BLE.setLocalName("LED");
    BLE.setAdvertisedService(ledService);

    // add the characteristic to the service
    ledService.addCharacteristic(switchCharacteristic);

    // add service
    BLE.addService(ledService);

    // set the initial value for the characeristic:
    switchCharacteristic.writeValue(0);

    // start advertising
    BLE.advertise();

    printf("BLE peripheral configured !\n\r");

    while (true) {
        // listen for BLE peripherals to connect:
        BLEDevice central = BLE.central();

        // if a central is connected to peripheral:
        if (central) {
            printf("Connected to central: ");
            // print the central's MAC address:
            printf("%s\n\r", central.address());

            // while the central is still connected to peripheral:
            while (central.connected()) {
                // if the remote device wrote to the characteristic,
                // use the value to control the LED:
                if (switchCharacteristic.written()) {
                    if (switchCharacteristic.value()) {  // any value other than 0
                        printf("LED on\n\r");
                        iotNode.io.led1.setDigitalValue(1);
                    }
                    else {  // a 0 value
                        printf("LED off\n\r");
                        iotNode.io.led1.setDigitalValue(0);
                    }
                }
            }

            // when the central disconnects, print it out:
            printf("Disconnected from central: ");
            printf("%s\n\r", central.address());
        }
    }
}
