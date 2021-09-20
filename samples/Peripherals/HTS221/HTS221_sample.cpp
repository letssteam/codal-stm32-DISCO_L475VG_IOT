
#include "HTS221_sample.h"

#include <string>

void hts221Sample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*          Demonstration du HTS221        *\r\n");
    printf("*******************************************\r\n");

    codal::HTS221 hts221(&discoL475VgIot.i2c2, 0xBE);
    hts221.init();

    hts221.setOutputRate(codal::HTS221_OUTPUT_RATE::RATE_1HZ);

    discoL475VgIot.sleep(2000);

    std::string temperature;
    std::string humidity;

    while (true) {
        while (!hts221.isTemperatureDataAvailable() || !hts221.isHumidityDataAvailable()) {
            discoL475VgIot.sleep(100);
        }

        temperature = "Temperature : " + std::to_string(hts221.getTemperature()) + " C";
        humidity    = "Humidity : " + std::to_string(hts221.getHumidity()) + " %RH";

        printf("%s \r\n", temperature.c_str());
        printf("%s \r\n", humidity.c_str());
        printf("\r\n");

        discoL475VgIot.sleep(1000);
    }
}
