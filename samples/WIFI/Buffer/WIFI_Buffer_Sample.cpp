#include <memory>

#include "Buffer.h"
#include "Ism43362Driver.h"
#include "WIFI_Http_Client_Sample.h"
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

Buffer<char> buffer;

void Wifi_Http_Client_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*          Demonstration du buffer        *\r\n");
    printf("*******************************************\r\n");

    buffer = 'a';
    buffer.put('b');
    char* head = buffer.head();
    puts(head);
    char whats_in_there[2] = {0};
    int pos                = 0;
    while (buffer.available()) {
        whats_in_there[pos++] = buffer;
    }
    printf("%c %c\r\n", whats_in_there[0], whats_in_there[1]);
    buffer.clear();
    printf("Done !\r\n");
}