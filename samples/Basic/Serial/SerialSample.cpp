#include "SerialSample.h"

#include <string>

#include "STM32Serial.h"

void SerialSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("* Demonstration de la communication serie *\r\n");
    printf("*******************************************\r\n");
    std::string str;

    while (true) {
        if (discoL475VgIot.serial.isReadable() != 0) {
            char c = static_cast<char>(discoL475VgIot.serial.getChar(codal::ASYNC));
            str += c;
            printf("< %c \r\n", c);
            printf("> %s \r\n", str.c_str());
        }
    }
}
