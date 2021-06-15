
#include "HTS221_sample.h"

#include <string>

using namespace codal;
using namespace std;

void hts221Sample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*          Demonstration du HTS221        *\r\n");
    printf("*******************************************\r\n");

    HTS221 hts(discoL475VgIot.i2c2, 0xBE);
    hts.init();

    hts.setOutputRate(HTS221_OUTPUT_RATE::RATE_1HZ);

    discoL475VgIot.sleep(2000);

    string tempStr;
    string humStr;

    while (true) {
        while (!hts.isTemperatureDataAvailable() || !hts.isHumidityDataAvailable()) {
            discoL475VgIot.sleep(100);
        }

        tempStr = "Temp : " + to_string(hts.getTemperature()) + " C";
        humStr  = "Hum : " + to_string(hts.getHumidity()) + " %RH";

        printf("%s \r\n", tempStr.c_str());
        printf("%s \r\n", humStr.c_str());

        discoL475VgIot.sleep(1000);
    }
}
