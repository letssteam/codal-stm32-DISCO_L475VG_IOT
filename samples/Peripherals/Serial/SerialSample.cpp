#include "SerialSample.h"
#include "STM32Serial.h"

using namespace codal;
using namespace std;

void SerialSample_main(){
    STM32IotNode iotNode;
    string str;

    iotNode.serial.init( 115200 );

    printf("\n");
    printf("*******************************************\n\r");
    printf("* Demonstration de la communication serie *\n\r");
    printf("*******************************************\n\r");

    while(true) {
        if( iotNode.serial.isReadable() != 0 ){
            char c = iotNode.serial.getChar(ASYNC);
            str += c;
            printf( "< %c \n\r",c);
            printf( "> %s \n\r",str.c_str());
        }
    }
}