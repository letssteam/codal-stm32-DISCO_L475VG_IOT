#include "WIFI_Http_Client_Sample.h"

#include "Ism43362Driver.h"
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

const char* ssid       = "SSID";
const char* passphrase = "PASSWORD";

void Wifi_Http_Client_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*          Demonstration du wifi          *\r\n");
    printf("*******************************************\r\n");

    if (DrvWiFi.ES_WIFI_Init() != ES_WIFI_STATUS_OK) {
        printf("Init not Ok\r\n");
        return;
    }

    printf("Init Ok\r\n");

    printf("Begin scan network\r\n");
    DrvWiFi.ES_WIFI_ListAccessPoints();
    printf("End scan network\r\n");

    printf("Number of network : %d\r\n", DrvWiFi.ES_WIFI_GetApNbr());

    if (DrvWiFi.ES_WIFI_Connect(ssid, passphrase, ES_WIFI_SEC_WPA2) != ES_WIFI_STATUS_OK) {
        printf("Connection to %s not Ok\r\n", ssid);
        DrvWiFi.ES_WIFI_Disconnect();
        return;
    }
    printf("Connected to %s\r\n", ssid);
}