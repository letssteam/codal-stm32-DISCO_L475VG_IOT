#include "I2CSample.h"

#include <cstdio>

#include "STM32I2C.h"

void I2CSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\n");
    printf("*******************************************\r\n");
    printf("*  Demonstration de la communication I2C  *\r\n");
    printf("*           --- Scanner I2C ---           *\r\n");
    printf("*******************************************\r\n");
    discoL475VgIot.sleep(2000);

    codal::STM32I2C i2c(discoL475VgIot.io.sda, discoL475VgIot.io.scl);

    while (true) {
        printf("   00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n");

        for (uint8_t i = 0; i < 8; i++) {
            printf("%2X ", (i << 4));

            for (uint8_t j = 0; j < 16; ++j) {
                if (i == 0 && j == 0) {
                    printf("xx ");
                    continue;
                }

                uint8_t address = ((i << 4) | j) << 1;

                if (i2c.isDeviceAvailable(address)) {
                    printf("%02X ", address);
                }
                else {
                    printf("-- ");
                }
            }
            printf("\r\n");
        }
        printf("\r\n\r\n");

        discoL475VgIot.sleep(2000);
    }
}
