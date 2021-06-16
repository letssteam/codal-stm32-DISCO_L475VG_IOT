#include "BLE_Serial_Sample.h"

#include "STM32SerialBLE.h"

codal::STM32DISCO_L475VG_IOT_IO io;
codal::STM32SPI spi3(io.miso3, io.mosi3, io.sclk3);
HCISpiTransportClass hci(spi3, SPBTLE_RF, pinNametoDigitalPin(PD_13), pinNametoDigitalPin(PE_6),
                         pinNametoDigitalPin(PA_8), 8000000, 0);
BLELocalDevice BLEObj(&hci);
BLELocalDevice& BLE = BLEObj;

void blePeripheralConnectHandler(const BLEDevice& central)
{
    printf("BLE Connected : %s\r\n", central.address().c_str());
}

void blePeripheralDisconnectHandler(const BLEDevice& central)
{
    printf("BLE Disconnected : %s\r\n", central.address().c_str());
}

void BLE_Serial_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*       Demonstration du Serial BLE       *\r\n");
    printf("*******************************************\r\n");

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
            discoL475VgIot.sleep(50);
        }
    }

    codal::STM32SerialBLE bleSerial("6E400001-B5A3-F393-E0A9-E50E24DCCA9E", "6E400002-B5A3-F393-E0A9-E50E24DCCA9E",
                                    "6E400003-B5A3-F393-E0A9-E50E24DCCA9E");

    BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
    BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
    BLE.setLocalName("STM32DISCO_L475VG");
    BLE.setAdvertisedService(bleSerial.getService());
    BLE.advertise();

    while (true) {
        io.led1.setDigitalValue(state ? 1 : 0);
        io.led2.setDigitalValue(state ? 0 : 1);

        if (bleSerial.available() > 0) {
            bleSerial.send("Recv " + std::to_string(bleSerial.available()) + " bytes");
            printf("Recv: %s\r\n", bleSerial.read().c_str());
        }

        discoL475VgIot.sleep(150);
        state = !state;
    }
}
