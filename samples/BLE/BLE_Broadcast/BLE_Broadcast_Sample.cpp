#include "BLE_Broadcast_Sample.h"

#include <string>

#include "STM32AdvertisingBLE.h"
#include "STM32duinoBLE.h"
#include "VL53L0X.h"

codal::STM32DISCO_L475VG_IOT_IO io;
codal::STM32SPI spi3(io.miso3, io.mosi3, io.sclk3);
HCISpiTransportClass hci(&spi3, SPBTLE_RF, pinNametoDigitalPin(PD_13), pinNametoDigitalPin(PE_6),
                         pinNametoDigitalPin(PA_8), 8000000, 0);
BLELocalDevice BLEObj(&hci);
BLELocalDevice& BLE = BLEObj;

codal::STM32AdvertisingBLE advertising;

#define ADVERTISING_UUID 0x181C

void BLE_Broadcast_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*      Demonstration du BLE Broadcast     *\r\n");
    printf("*******************************************\r\n");

    codal::VL53L0X vl53l0x(&discoL475VgIot.i2c2, &discoL475VgIot.io.pc6, 0x52);

    vl53l0x.init();

    bool state = false;

    if (BLE.begin() != 0) {
        printf("BLE Initialized !\r\n");
    }
    else {
        printf("Failed to initialize BLE !!\r\n");

        while (true) {
            io.led2.setDigitalValue(state ? 1 : 0);
            io.led1.setDigitalValue(state ? 1 : 0);
            state = !state;
            discoL475VgIot.sleep(50);
        }
    }

    advertising.setLocalName("Youpi !");
    advertising.setServiceData(ADVERTISING_UUID, (uint8_t*)"Distance sensor !", 17);
    advertising.setDurationScanning(0);
    advertising.begin();

    int size;
    char message[22];
    BLEDevice buffer[16];

    while (true) {
        io.led1.setDigitalValue(state ? 0 : 1);
        io.led2.setDigitalValue(state ? 1 : 0);
        state = !state;

        size = sprintf(message, "D: %d", vl53l0x.getDistance());
        if (size >= 0) {
            advertising.setServiceData(ADVERTISING_UUID, (uint8_t*)message, size);
        }

        discoL475VgIot.sleep(500);
    }
}
