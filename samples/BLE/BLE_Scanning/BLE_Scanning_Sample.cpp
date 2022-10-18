#include "BLE_Scanning_Sample.h"

#include <cstdio>

#include "BLEDevice_Component.h"
#include "HCI_SPI.h"
#include "ble_utils.h"

codal::BLEDevice_Component* ble;
HCI_SPI* hci;

void BLE_Scanning_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*         Demonstration du Scan BLE       *\r\n");
    printf("*******************************************\r\n");

    hci = new HCI_SPI(discoL475VgIot.spi3, discoL475VgIot.io.bleCS, discoL475VgIot.io.bleIRQ, discoL475VgIot.io.bleRST);
    ble = new codal::BLEDevice_Component((uint16_t)12345, hci);

    // hci->enableDebug();
    ble->init();

    ble->startScanning();

    while (1) {
        discoL475VgIot.sleep(100);

        if (ble->availableScan()) {
            for (auto dev : ble->getScanResult()) {
                printf("Device:\r\n");
                printf("\tAddress: %s\r\n", dev.getAddress().toString().c_str());
                printf("\tRSSI: %ddBm\r\n", dev.getRSSI());
                printf("\tName: %s\r\n", dev.getName().c_str());
                printf("\tService data: \r\n");
                for (auto sd : dev.getAllServiceDatas()) {
                    printf("\t\t[%s] %s\r\n", BLE_Utils::hexToString(sd.uuid).c_str(),
                           BLE_Utils::dataToSafeString(sd.data).c_str());
                }
                printf("\r\n");
            }

            printf("--------------------------------------------------------------------------------\r\n\r\n");
        }
    }
}
