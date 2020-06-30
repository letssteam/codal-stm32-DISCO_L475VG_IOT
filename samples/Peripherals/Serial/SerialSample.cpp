#include "SerialSample.h"

void SerialSample_main(){
    codal::STM32IotNode iotNode;
    
    printf("\n");
    printf("*******************************************\n");
    printf("* Demonstration de la communication serie *\n");
    printf("*******************************************\n");
    
    iotNode.sleep(1000);
    
    while(1) {
        iotNode.io.led1.setDigitalValue(1);

        printf("\nVALUE = %d.%d degC\n", 0, 0);

        iotNode.io.led1.setDigitalValue(0);
        iotNode.sleep(1000);
    }
}