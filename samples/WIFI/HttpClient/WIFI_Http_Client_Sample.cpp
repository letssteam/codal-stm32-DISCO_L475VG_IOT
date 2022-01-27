#include "WIFI_Http_Client_Sample.h"

#include "ssd1306.h"
extern codal::STM32Pin commandDataReadyPin;

void Wifi_Http_Client_Sample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    codal::SSD1306_I2C oled(&discoL475VgIot.i2c1, 0x78, 128, 64, false);

    oled.init();
    oled.fill(0);
    oled.drawText("Demo wifi", 0, 0, 1);
    oled.show();

    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*          Demonstration du wifi          *\r\n");
    printf("*******************************************\r\n");
    std::string str;

    if (SPI_WIFI_Init(ES_WIFI_INIT) != 0) {
        printf("Init not Ok\r\n");
        return;
    }

    printf("Init Ok\r\n");

    int ret = SPI_WIFI_SendData((uint8_t*)"I?\r\n", 4, ES_WIFI_TIMEOUT);
    if (ret != 4) {
        printf("Init command not sent!\r\n");
        return;
    }

    printf("Init command sent!\r\n");

    uint8_t receivedData[ES_WIFI_DATA_SIZE];
    int receiveLength = SPI_WIFI_ReceiveData(receivedData, ES_WIFI_DATA_SIZE, ES_WIFI_TIMEOUT);
    if (receiveLength < 0) {
        printf("Problem during receive data\r\n");
        return;
    }
    printf("Data Received : %d\r\n", receiveLength);
    for (int i = 0; i < receiveLength; i++) {
        printf("receivedData[%d] = %d\r\n", i, receivedData[i]);
    }
}