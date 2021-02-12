#include <array>
#include "LSM6DSL_sample.h"

using namespace codal;
using namespace std;

void lsm6dslSample(){

    STM32IotNode iotNode;
    LSM6DSL accelGyro( iotNode.i2c2, 0xD4 );

    iotNode.serial.init(115200);
    accelGyro.init();



    printf("\n");
    printf("****************\n\r");
    printf("* LSM6DSL TEST *\n\r");
    printf("****************\n\r");

    array<float, 3> gyro;
    array<float, 3> accel;

    while(true){
        gyro = accelGyro.getGyroscopeMeasure();
        accel = accelGyro.getAccelerometerMeasure();

        printf("Accel [G] : %5.3f %5.3f %5.3f | Gyro [°/s (dps)] : %5.3f %5.3f %5.3f\n\r", accel[0], accel[1], accel[2], gyro[0], gyro[1], gyro[2]);

        iotNode.sleep(100);
    }

}
