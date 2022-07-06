#include "BLE_Broadcast_and_Scan_Sample.h"

// #include <string>

// #include "STM32AdvertisingBLE.h"
// #include "STM32duinoBLE.h"

// codal::STM32DISCO_L475VG_IOT_IO io;
// codal::STM32SPI spi3(io.miso3, io.mosi3, io.sclk3);
// HCISpiTransportClass hci(&spi3, SPBTLE_RF, pinNametoDigitalPin(PD_13), pinNametoDigitalPin(PE_6),
//                          pinNametoDigitalPin(PA_8), 8000000, 0);
// BLELocalDevice BLEObj(&hci);
// BLELocalDevice& BLE = BLEObj;

// codal::STM32AdvertisingBLE advertising;

// #define ADVERTISING_UUID 0x181C

// char get_safe_char(uint8_t c)
// {
//     if (c >= 32 && c <= 126) {
//         return (char)c;
//     }
//     else {
//         return '?';
//     }
// }

// void print_message(std::vector<uint8_t> data)
// {
//     for (auto d : data) {
//         printf("%02X ", d);
//     }

//     printf("\r\n");
// }

// void print_message_as_string(std::vector<uint8_t> data)
// {
//     for (auto c : data) {
//         printf("%c", get_safe_char(c));
//     }

//     printf("\r\n");
// }

// void print_scan_result()
// {
//     if (advertising.hasReceivedMessage()) {
//         auto results = advertising.getAllReceivedMessage();

//         for (auto res : results) {
//             printf("%s\n\r", res.address.c_str());
//             printf("\tRSSI:         %d dbm\r\n", res.rssi);
//             printf("\tName:         %s\r\n", res.name.c_str());
//             printf("\tUUID:         %s\r\n", res.uuid.c_str());
//             printf("\tData (raw):   ");
//             print_message(res.message);
//             printf("\tData (UTF-8): ");
//             print_message_as_string(res.message);
//             printf("\r\n");
//         }

//         printf("\n\r===================================================================\n\r\n\r");
//     }
// }

// void BLE_Broadcast_and_Scan_sample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
// {
//     unsigned ms = 0;

//     discoL475VgIot.serial.init(115200);

//     printf("\r\n");
//     printf("*******************************************\r\n");
//     printf("*           Demonstration du BLE          *\r\n");
//     printf("*******************************************\r\n");

//     if (BLE.begin() != 0) {
//         printf("BLE Initialized !\r\n");
//     }
//     else {
//         printf("Failed to initialize BLE !!\r\n");
//         bool state = false;

//         while (true) {
//             io.led2.setDigitalValue(state ? 1 : 0);
//             io.led1.setDigitalValue(state ? 1 : 0);
//             state = !state;
//             discoL475VgIot.sleep(50);
//         }
//     }

//     advertising.setLocalName("It Work's !");
//     advertising.setServiceData(ADVERTISING_UUID, (uint8_t*)"Start counter !", 15);
//     advertising.begin();

//     int size;
//     char message[22];
//     BLEDevice buffer[16];

//     while (true) {
//         io.led1.setDigitalValue(advertising.isEmitting() ? 1 : 0);
//         io.led2.setDigitalValue(advertising.isScanning() ? 1 : 0);

//         if (ms % 1000 && advertising.isScanning()) {
//             print_scan_result();
//         }

//         if (ms % 1000 && advertising.isEmitting()) {
//             size = sprintf(message, "Time: %02d", ms / 1000);
//             if (size >= 0) {
//                 advertising.setServiceData(ADVERTISING_UUID, (uint8_t*)message, size);
//             }
//         }

//         ms += 100;
//         discoL475VgIot.sleep(100);
//     }
// }
