#include "SerialSample.h"
#include "STM32Serial.h"
#include <string>

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

    while(1) {
        if( iotNode.serial.isReadable() ){
            char c = iotNode.serial.getChar(ASYNC);
            str += c;
            printf( string("< " + string(1, c) + "\n\r").c_str() );
            printf( string("> " + str + "\n\r").c_str() );
        }
    }
}