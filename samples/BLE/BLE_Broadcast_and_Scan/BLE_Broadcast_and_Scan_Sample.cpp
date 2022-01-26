#include "BLE_Broadcast_and_Scan_Sample.h"

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

#define ST_MICRO_COMPANY_UUID 0x0030

char get_safe_char(uint8_t c)
{
    if (c >= 32 && c <= 126) {
        return (char)c;
    }
    else {
        return '?';
    }
}

void print_manufacturer_data(BLEDevice& device)
{
    size_t nb = device.manufacturerDataCount();
    for (size_t i = 0; i < nb; ++i) {
        auto manData    = device.getManufacturerData(i);
        std::string str = "";
        printf("\t\t#%d: 0x%04X - ", i + 1, manData.companyIdentifier);

        for (size_t j = 0; j < manData.data.size(); j++) {
            printf("%02X", manData.data[j]);
            str += get_safe_char(manData.data[j]);
        }
        printf(" ('%s')\n\r", str.c_str());
    }
}

void print_advertising_data(BLEDevice& device)
{
    size_t nb = device.advertisingDataCount();
    for (size_t i = 0; i < nb; ++i) {
        auto data       = device.getAdvertisingData(i);
        std::string str = "";
        printf("\t\t#%d: ", i + 1);

        for (size_t j = 0; j < data.size(); j++) {
            printf("%02X", data[j]);

            if (j >= 2) {
                str += get_safe_char(data[j]);
            }
        }
        printf(" ('%s')\n\r", str.c_str());
    }
}

void print_advertised_services_uuid(BLEDevice& device)
{
    for (int j = 0; j < device.advertisedServiceUuidCount(); ++j) {
        printf("\t\tUUID : %s\n\r", device.advertisedServiceUuid(j).c_str());
    }
}

void print_scan_result()
{
    BLEDevice buffer[16];

    if (advertising.hasResultWithManufacturerData()) {
        size_t nb_result = advertising.getResultWithManufacturerData(buffer, 16);

        for (size_t device_index = 0; device_index < nb_result; ++device_index) {
            BLEDevice device = buffer[device_index];

            printf("[%d dBm] %s : %s\n\r", device.rssi(), device.address().c_str(),
                   device.hasLocalName() ? device.localName().c_str() : "N/A");

            printf("\t=> Manufacturer Data:\n\r");
            print_manufacturer_data(device);

            printf("\t=> Advertising Data:\n\r");
            print_advertising_data(device);

            printf("\t=> Advertised services:\n\r");
            print_advertised_services_uuid(device);

            printf("\n\r");
        }

        printf("\n\r===================================================================\n\r\n\r");
    }
}

void BLE_Broadcast_and_Scan_sample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    unsigned ms = 0;

    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*           Demonstration du BLE          *\r\n");
    printf("*******************************************\r\n");

    if (BLE.begin() != 0) {
        printf("BLE Initialized !\r\n");
    }
    else {
        printf("Failed to initialize BLE !!\r\n");
        bool state = false;

        while (true) {
            io.led2.setDigitalValue(state ? 1 : 0);
            io.led1.setDigitalValue(state ? 1 : 0);
            state = !state;
            discoL475VgIot.sleep(50);
        }
    }

    advertising.setLocalName("It Work's !");
    advertising.setManufacturerData(ST_MICRO_COMPANY_UUID, (uint8_t*)"Start counter !", 15);
    advertising.begin();

    int size;
    char message[22];
    BLEDevice buffer[16];

    while (true) {
        io.led1.setDigitalValue(advertising.isEmitting() ? 1 : 0);
        io.led2.setDigitalValue(advertising.isScanning() ? 1 : 0);

        if (ms % 1000 && advertising.isScanning()) {
            print_scan_result();
        }

        if (ms % 1000 && advertising.isEmitting()) {
            size = sprintf(message, "Time: %02d", ms / 1000);
            if (size >= 0) {
                advertising.setManufacturerData(ST_MICRO_COMPANY_UUID, (uint8_t*)message, size);
            }
        }

        ms += 100;
        discoL475VgIot.sleep(100);
    }
}
