#include "BLE_Broadcast_Sample.h"

#include <cstdio>

#include "AdvertisingData.h"
#include "AdvertisingFlagsBuilder.h"
#include "BLEDevice.h"
#include "HCI_SPI.h"
#include "STM32Serial.h"
#include "ble_utils.h"

void BLE_Broadcast_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*      Demonstration broadcast du BLE     *\r\n");
    printf("*******************************************\r\n");

    HCI_SPI hci(discoL475VgIot.spi3, discoL475VgIot.io.bleCS, discoL475VgIot.io.bleIRQ, discoL475VgIot.io.bleRST);
    BLEDevice ble(&hci);

    AdvertisingData adv;
    AdvertisingData advScan;

    // hci.enableDebug();
    ble.init();

    uint8_t flags = AdvertisingFlagsBuilder().addBrEdrNotSupported().addLeGeneralDiscoverableMode().build();
    adv.setFlags(flags);
    adv.setLocalName("Broadcast test");
    adv.setUserData("User data !");

    advScan.setUserData("Hi ! I'm scan response !");

    if (ble.startAdvertising(adv, advScan) != BLEDeviceError::SUCCESS) {
        printf("Failed to start BLE !");
    }

    while (1) {
        discoL475VgIot.sleep(1000);

        adv.setUserData(std::to_string(getCurrentMillis() / 1000) + " sec");
        ble.setAdvertisingData(adv);
    }
}
