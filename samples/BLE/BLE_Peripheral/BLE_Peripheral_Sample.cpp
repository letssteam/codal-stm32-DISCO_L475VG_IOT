#include "BLE_Peripheral_Sample.h"

#include "STM32duinoBLE.h"

codal::STM32DISCO_L475VG_IOT_IO io;
codal::STM32SPI spi3(io.miso3, io.mosi3, io.sclk3);
HCISpiTransportClass hci(&spi3, SPBTLE_RF, pinNametoDigitalPin(PD_13), pinNametoDigitalPin(PE_6),
                         pinNametoDigitalPin(PA_8), 8000000, 0);
BLELocalDevice BLEObj(&hci);
BLELocalDevice& BLE = BLEObj;

void BLE_Peripheral_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*  Demonstration du Bluetooth Low Energy  *\r\n");
    printf("*******************************************\r\n");

    BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214");
    BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

    bool state = false;

    if (BLE.begin() != 0) {
        printf("BLE Initialized !\r\n");
    }
    else {
        printf("Failed to initialize BLE !!\r\n");

        while (true) {
            io.led2.setDigitalValue(state ? 1 : 0);
            io.led1.setDigitalValue(state ? 0 : 1);
            state = !state;
            discoL475VgIot.sleep(100);
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

    printf("BLE peripheral configured !\r\n");

    while (true) {
        // listen for BLE peripherals to connect:
        BLEDevice central = BLE.central();

        // if a central is connected to peripheral:
        if (central) {
            printf("Connected to central: ");
            // print the central's MAC address:
            printf("%s\r\n", central.address().c_str());

            // while the central is still connected to peripheral:
            while (central.connected()) {
                // if the remote device wrote to the characteristic,
                // use the value to control the LED:
                if (switchCharacteristic.written()) {
                    if (switchCharacteristic.value() != 0U) {
                        printf("LED on\r\n");
                        io.led1.setDigitalValue(1);
                    }
                    else {
                        printf("LED off\r\n");
                        io.led1.setDigitalValue(0);
                    }
                }
            }

            // when the central disconnects, print it out:
            printf("Disconnected from central: ");
            printf("%s\r\n", central.address().c_str());
        }
    }
}
