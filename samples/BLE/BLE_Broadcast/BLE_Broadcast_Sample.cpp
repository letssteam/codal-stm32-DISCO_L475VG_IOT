#include "BLE_Broadcast_Sample.h"

#include <string>

#include "STM32AdvertisingBLE.h"
#include "STM32duinoBLE.h"

codal::STM32DISCO_L475VG_IOT_IO io;
codal::STM32SPI spi3(io.miso3, io.mosi3, io.sclk3);
HCISpiTransportClass hci(spi3, SPBTLE_RF, pinNametoDigitalPin(PD_13), pinNametoDigitalPin(PE_6),
                         pinNametoDigitalPin(PA_8), 8000000, 0);
BLELocalDevice BLEObj(&hci);
BLELocalDevice& BLE = BLEObj;

codal::STM32AdvertisingBLE advertising(DEVICE_ID_RADIO);

#define ST_MICRO_COMPANY_UUID 0x0030

void BLE_Broadcast_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*      Demonstration du BLE Broadcast     *\r\n");
    printf("*******************************************\r\n");

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
    advertising.setManufacturerData(ST_MICRO_COMPANY_UUID, "Start counter !");
    advertising.setDurationScanning(0);
    advertising.begin();

    std::string message;
    unsigned ms = 0;
    BLEDevice buffer[16];

    while (true) {
        io.led1.setDigitalValue(state ? 0 : 1);
        io.led2.setDigitalValue(state ? 1 : 0);
        state = !state;

        if (ms % 1000) {
            message = "Time: " + std::to_string(ms / 1000);
            advertising.setManufacturerData(ST_MICRO_COMPANY_UUID, message.c_str());
        }

        ms += 500;
        discoL475VgIot.sleep(500);
    }
}
