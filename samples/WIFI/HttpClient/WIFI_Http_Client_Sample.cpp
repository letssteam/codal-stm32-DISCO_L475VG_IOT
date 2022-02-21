#include <memory>

#include "Ism43362Driver.h"
#include "WIFI_Buffer_Sample.h"
#include "Wifi.h"
#include "ssd1306.h"

codal::STM32Pin miso3(ID_PIN_WIFI_ISM43362_MISO, PinNumber::PC_11, codal::PIN_CAPABILITY_DIGITAL);
codal::STM32Pin mosi3(ID_PIN_WIFI_ISM43362_MOSI, PinNumber::PC_12, codal::PIN_CAPABILITY_DIGITAL);
codal::STM32Pin sclk3(ID_PIN_WIFI_ISM43362_SCK, PinNumber::PC_10, codal::PIN_CAPABILITY_DIGITAL);

codal::STM32SPI spi3(miso3, mosi3, sclk3, 10000000UL, 0, true);

codal::STM32Pin wakeUpPin(ID_PIN_WIFI_ISM43362_WAKE_UP, PinNumber::PB_13, codal::PIN_CAPABILITY_DIGITAL);
codal::STM32Pin resetPin(ID_PIN_WIFI_ISM43362_RESET, PinNumber::PE_8, codal::PIN_CAPABILITY_DIGITAL);
codal::STM32Pin csPin(ID_PIN_WIFI_ISM43362_CS, PinNumber::PE_0, codal::PIN_CAPABILITY_DIGITAL);
codal::STM32Pin commandDataReadyPin(ID_PIN_WIFI_ISM43362_COMMAND_DATA_READY, PinNumber::PE_1,
                                    codal::PIN_CAPABILITY_DIGITAL);

Ism43362Driver DrvWiFi(&spi3, &csPin, &commandDataReadyPin, &resetPin, &wakeUpPin);
codal::WiFi wifi(DrvWiFi);

const char* ssid       = "NEDJAR";
const char* passphrase = "Camevenere1!";
const char* host       = "google.com";
const char* methodName = "GET";

void Wifi_Buffer_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*          Demonstration du wifi          *\r\n");
    printf("*******************************************\r\n");

    if (wifi.init() != DEVICE_OK) {
        printf("Init not Ok\r\n");
        return;
    }
    else
        printf("Init Ok\r\n");

    printf("Number of network : %d \r\n", wifi.networksVisible());

    printf("Connection to %s \r\n", ssid);

    wifi.attach(ssid, passphrase);

    if (!wifi.isAttached()) {
        printf("Not connected to %s \r\n", ssid);
        wifi.detach();
        return;
    }

    printf("Connected to %s \r\n", ssid);

    auto client = wifi.connect(host, 80);

    if (client->isConnected()) {
        auto req = "GET / HTTP/1.1\r\nHost: google.com\r\nConnection: Close\r\n\r\n";
        client->write(req, strlen(req));
        char buffer[2000];
        memset(buffer, 0, 2000);
        client->read(buffer, 2000);
        printf("Received : %s\r\n", buffer);
    }
}