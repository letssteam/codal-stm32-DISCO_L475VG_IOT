#include "LSM6DSL_sample.h"

#include <array>
#include <cstdio>

void lsm6dslSample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    discoL475VgIot.serial.init(115200);

    printf("\r\n");
    printf("*******************************************\r\n");
    printf("*         Demonstration du LSM6DSL        *\r\n");
    printf("*******************************************\r\n");

    codal::LSM6DSL lsm6dsl(&discoL475VgIot.i2c2, 0xD4);
    lsm6dsl.init();

    std::array<float, 3> gyroscopeMeasure;
    std::array<float, 3> accelerometerMeasure;

    while (true) {
        gyroscopeMeasure     = lsm6dsl.getGyroscopeMeasure();
        accelerometerMeasure = lsm6dsl.getAccelerometerMeasure();

        printf("Accelerometer [G] : %5.3f %5.3f %5.3f\r\n", accelerometerMeasure[0], accelerometerMeasure[1],
               accelerometerMeasure[2]);
        printf("Gyroscope [°/s (dps)] : %5.3f %5.3f %5.3f\r\n", gyroscopeMeasure[0], gyroscopeMeasure[1],
               gyroscopeMeasure[2]);
        printf("\r\n");

        discoL475VgIot.sleep(1000);
    }
}
