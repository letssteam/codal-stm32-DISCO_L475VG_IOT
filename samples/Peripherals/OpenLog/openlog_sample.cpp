#include "openlog_sample.h"

#include <cstdio>

#include "HTS221.h"
#include "LPS22HB.h"
#include "openlog.h"

codal::OpenLog* openLogWriter;

void openLogSample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);
    openLogWriter = new codal::OpenLog(discoL475VgIot.io.D1, discoL475VgIot.io.D0, discoL475VgIot.io.D2);

    codal::LPS22HB lps22hb(&discoL475VgIot.i2c2, 0xBA);
    lps22hb.init();

    codal::HTS221 hts221(&discoL475VgIot.i2c2, 0xBE);
    hts221.init();
    hts221.setOutputRate(codal::HTS221_OUTPUT_RATE::RATE_1HZ);

    printf("****************************************************\r\n");
    printf("*         Demonstration du lecteur OpenLog         *\r\n");
    printf("****************************************************\r\n");

    char* sensorData   = (char*)malloc(100);
    char* columnsNames = "temperature (°C);pressure (Pa);humidity (%)\r\n";
    bool isDataTransferOK;

    isDataTransferOK = openLogWriter->write(columnsNames, strlen(columnsNames));
    printf("ecriture des en têtes de colonne %s", (isDataTransferOK) ? "reussie" : "echouee :(");

    float temperature, pressure, humidity;
    while (true) {
        temperature = lps22hb.getTemperature();
        pressure    = lps22hb.getPressure();
        while (!hts221.isHumidityDataAvailable()) {
            discoL475VgIot.sleep(100);
        }
        humidity = hts221.getHumidity();

        unsigned dataSize = snprintf(NULL, 0, "%f;%f;%f\r\n", temperature, pressure, humidity);
        snprintf(sensorData, dataSize, "%f;%f;%f\r\n", temperature, pressure, humidity);
        printf("ecriture des donnees suivantes sur la carte micro-sd :\r\n%s\r\n", sensorData);
        isDataTransferOK = openLogWriter->write(sensorData, dataSize);
        printf("ecriture %s\r\n\r\n", (isDataTransferOK) ? "reussie" : "echouee");
        discoL475VgIot.sleep(1000);
    }
}
