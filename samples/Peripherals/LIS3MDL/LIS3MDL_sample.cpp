
#include "LIS3MDL_sample.h"

using namespace codal;
using namespace std;

void lis3mdlSample(){

    STM32IotNode iotNode;
    LIS3MDL magneto(iotNode.i2c2, 0x3C);

    iotNode.serial.init(115200);
    magneto.init();

    printf("\n");
    printf("************************\n\r");
    printf("***** Test LIS3MDL *****\n\r");
    printf("************************\n\r");



    while(true){

        auto values = magneto.getMeasure();

        printf("X : %5ld\tY : %5ld\tZ : %5ld\n\r", values[0], values[1], values[2]);

        iotNode.sleep(500);
    }

}