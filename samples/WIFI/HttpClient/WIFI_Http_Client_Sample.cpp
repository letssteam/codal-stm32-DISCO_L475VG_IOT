#include "WIFI_Http_Client_Sample.h"

#include "ISM43362_M3G_L44_driver.h"
#include "es_wifi_conf.h"
#include "ssd1306.h"

codal::STM32Pin miso3(ID_PIN_WIFI_MISO, PinNumber::PC_11, codal::PIN_CAPABILITY_DIGITAL);
codal::STM32Pin mosi3(ID_PIN_WIFI_MOSI, PinNumber::PC_12, codal::PIN_CAPABILITY_DIGITAL);
codal::STM32Pin sclk3(ID_PIN_WIFI_SCLK, PinNumber::PC_10, codal::PIN_CAPABILITY_DIGITAL);

codal::STM32SPI spi3(miso3, mosi3, sclk3, 10000000UL, 0, true);

IsmDrvClass DrvWiFi(&spi3, PinNumber::PE_0, PinNumber::PE_1, PinNumber::PE_8, PinNumber::PB_13);

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