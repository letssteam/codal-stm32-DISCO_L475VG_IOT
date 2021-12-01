#include "BLE_Broadcast_Sample.h"

#include "STM32BLEAdvertising.h"

// #include "STM32duinoBLE.h"

// codal::STM32DISCO_L475VG_IOT_IO io;
// codal::STM32SPI spi3(io.miso3, io.mosi3, io.sclk3);
// HCISpiTransportClass hci(spi3, SPBTLE_RF, pinNametoDigitalPin(PD_13), pinNametoDigitalPin(PE_6),
//                          pinNametoDigitalPin(PA_8), 8000000, 0);
// BLELocalDevice BLEObj(&hci);
// BLELocalDevice& BLE = BLEObj;

void BLE_Broadcast_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    codal::STM32BLEAdvertising advrt();

    // discoL475VgIot.serial.init(115200);

    // printf("\r\n");
    // printf("*******************************************\r\n");
    // printf("*      Demonstration du BLE Broadcast     *\r\n");
    // printf("*******************************************\r\n");

    // bool state = false;

    // if (BLE.begin() != 0) {
    //     printf("BLE Initialized !\r\n");
    // }
    // else {
    //     printf("Failed to initialize BLE !!\r\n");

    //     while (true) {
    //         io.led2.setDigitalValue(state ? 1 : 0);
    //         io.led1.setDigitalValue(state ? 1 : 0);
    //         state = !state;
    //         discoL475VgIot.sleep(50);
    //     }
    // }

    // const char* advDataStr = "My broadcast message !";

    // BLEAdvertisingData advData;
    // advData.setAdvertisedServiceData(0x1800, (uint8_t*)(advDataStr), strlen(advDataStr));

    // BLE.setAdvertisingData(advData);
    // BLE.setLocalName("My Device");
    // BLE.setConnectable(false);
    // BLE.advertise(37);

    // while (true) {
    //     io.led2.setDigitalValue(state ? 1 : 0);
    //     io.led1.setDigitalValue(state ? 0 : 1);
    //     state = !state;
    //     discoL475VgIot.sleep(150);
    // }
}
