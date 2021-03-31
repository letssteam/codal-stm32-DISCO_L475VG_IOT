
#include "LIS3MDL_sample.h"

using namespace codal;
using namespace std;

void lis3mdlSample()
{
    STM32IotNode iotNode;
    iotNode.init();

    LIS3MDL magneto(iotNode.i2c2, 0x3C);

    iotNode.serial.init(115200);
    magneto.init();

    printf("\n");
    printf("************************\n\r");
    printf("***** Test LIS3MDL *****\n\r");
    printf("************************\n\r");

    while (true) {
        auto values = magneto.getMeasure();

        printf("X : %5u\tY : %5u\tZ : %5u\n\r", values[0], values[1], values[2]);

        codal::STM32IotNode::sleep(500);
    }
}
