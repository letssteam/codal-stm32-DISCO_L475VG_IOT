#include "BLE_Scanning_Sample.h"

#include <string>

#include "STM32AdvertisingBLE.h"
#include "STM32duinoBLE.h"

codal::STM32DISCO_L475VG_IOT_IO io;
codal::STM32SPI spi3(io.miso3, io.mosi3, io.sclk3);
HCISpiTransportClass hci(&spi3, SPBTLE_RF, pinNametoDigitalPin(PD_13), pinNametoDigitalPin(PE_6),
                         pinNametoDigitalPin(PA_8), 8000000, 0);
BLELocalDevice BLEObj(&hci);
BLELocalDevice& BLE = BLEObj;

codal::STM32AdvertisingBLE advertising;

char get_safe_char(uint8_t c)
{
    if (c >= 32 && c <= 126) {
        return (char)c;
    }
    else {
        return '?';
    }
}

void print_message(std::vector<uint8_t> data)
{
    for (auto d : data) {
        printf("%02X ", d);
    }

    printf("\r\n");
}

void print_message_as_string(std::vector<uint8_t> data)
{
    for (auto c : data) {
        printf("%c", get_safe_char(c));
    }

    printf("\r\n");
}

void print_scan_result()
{
    if (advertising.hasReceivedMessage()) {
        auto results = advertising.getAllReceivedMessage();

        for (auto res : results) {
            printf("%s\n\r", res.address.c_str());
            printf("\tRSSI:         %d dbm\r\n", res.rssi);
            printf("\tName:         %s\r\n", res.name.c_str());
            printf("\tUUID:         %s\r\n", res.uuid.c_str());
            printf("\tData (raw):   ");
            print_message(res.message);
            printf("\tData (UTF-8): ");
            print_message_as_string(res.message);
            printf("\r\n");
        }

        printf("\n\r===================================================================\n\r\n\r");
    }
}

void BLE_Scanning_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    bool state     = false;
    unsigned sleep = 10;
    unsigned ms    = 0;

    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*         Demonstration du Scan BLE       *\r\n");
    printf("*******************************************\r\n");

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

    advertising.setDurationEmitting(0);
    advertising.begin();

    while (true) {
        io.led1.setDigitalValue(state ? 0 : 1);
        io.led2.setDigitalValue(state ? 1 : 0);
        state = !state;

        if (ms >= 250) {
            printf("Scan result:\r\n");
            print_scan_result();
            ms = 0;
        }

        ms += sleep;
        discoL475VgIot.sleep(sleep);
    }
}
