#include "BLE_Broadcast_Sample.h"

#include <cstdio>

#include "AdvertisingData.h"
#include "BLEDevice.h"
#include "HCI_SPI.h"
#include "STM32Serial.h"
#include "ble_utils.h"
#include "AdvertisingFlagsBuilder.h"

void BLE_Broadcast_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*           Demonstration du BLE          *\r\n");
    printf("*******************************************\r\n");

    HCI_SPI hci(discoL475VgIot.spi3, discoL475VgIot.io.bleCS, discoL475VgIot.io.bleIRQ, discoL475VgIot.io.bleRST);
    BLEDevice ble(&hci);

    AdvertisingData adv;
    AdvertisingData advScan;

    // hci.enableDebug();
    ble.init();

    printf("\n==> Get BD Address\r\n");
    auto addr = hci.readBD_ADDR();

    printf("\t");
    BLE_Utils::printHex(addr[0]);
    printf("\r\n");

    printf("\t");
    BLE_Utils::printHex(addr[1]);
    printf("\r\n");

    printf("\n==> Get Random value\r\n");
    auto rnd = hci.leRand();

    printf("\t");
    BLE_Utils::printHex(rnd[0]);
    printf("\r\n");

    printf("\t");
    BLE_Utils::printHex(rnd[1]);
    printf("\r\n");

    uint8_t flags = AdvertisingFlagsBuilder().addBrEdrNotSupported().addLeGeneralDiscoverableMode().build();
    adv.setFlags(flags);
    adv.setLocalName("Broadcast test");
    adv.setUserData("User data !");

    advScan.setUserData("Hi ! I'm scan response !");

    ble.setAdvertisingData(&adv);
    ble.setScanResponseData(&advScan);
    if (ble.startAdvertising() != BLEDeviceError::SUCCESS) {
        printf("Failed to start BLE !");
    }

    while (1) {
        discoL475VgIot.sleep(1000);

        adv.setUserData(std::to_string(getCurrentMillis() / 1000) + " sec");
        ble.updateAdvertisingData();
    }
}
