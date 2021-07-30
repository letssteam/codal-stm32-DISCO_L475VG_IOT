#include "SpiSample.h"

#include <cstdio>

#include "STM32SPI.h"

void sendWithTransaction(codal::STM32SPI* spi, uint8_t sendVal)
{
    spi->beginTransaction();
    spi->writeTransaction(sendVal);
    auto val = spi->endTransaction();

    printf("[Transaction] Send value : %d\r\n", sendVal);
    printf("[Transaction] Received value : %d\r\n", val[0]);
}

void sendWithWrite(codal::STM32SPI* spi, uint8_t sendVal)
{
    auto val = spi->write(sendVal);

    printf("[Write Func] Send value : %d\r\n", sendVal);
    printf("[Write Func] Received value : %d\r\n", val);
}

void SpiSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\n");
    printf("*******************************************\r\n");
    printf("*  Demonstration de la communication SPI  *\r\n");
    printf("*******************************************\r\n");
    discoL475VgIot.sleep(2000);

    codal::STM32SPI spi(discoL475VgIot.io.miso, discoL475VgIot.io.mosi, discoL475VgIot.io.sclk, 1400000);

    bool state      = false;
    uint8_t sendVal = 0;

    while (true) {
        sendWithTransaction(&spi, sendVal);
        sendWithWrite(&spi, sendVal);
        printf("\r\n");

        discoL475VgIot.io.led2.setDigitalValue(static_cast<int>(state));
        state = !state;
        sendVal++;

        discoL475VgIot.sleep(2000);
    }
}
