#include "LPS22HB_sample.h"

#include <string>

using std::string;
using std::to_string;

void lps22hbSample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*         Demonstration du LPS22HB        *\r\n");
    printf("*******************************************\r\n");

    codal::LPS22HB lps22hb(discoL475VgIot.i2c2, 0xBA);
    lps22hb.init();

    discoL475VgIot.sleep(2000);

    string pressure;
    string temperature;

    while (true) {
        pressure    = "Pressure : " + to_string(lps22hb.getPressure()) + "hPa";
        temperature = "Temperature : " + to_string(lps22hb.getTemperature()) + "C";

        printf("%s \r\n", pressure.c_str());
        printf("%s \r\n", temperature.c_str());
        printf("\r\n");

        discoL475VgIot.sleep(1000);
    }
}
