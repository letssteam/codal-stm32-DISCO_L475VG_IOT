#include "SpiSample.h"

#include "STM32SPI.h"

using namespace codal;
using namespace std;


void sendWithTransaction(STM32SPI& spi, uint8_t sendVal){
    spi.beginTransaction();
    spi.writeTransaction(sendVal);
    auto val = spi.endTransaction();

    printf("[Transaction] Send value : %d\n\r", sendVal);
    printf("[Transaction] Received value : %d\n\r", val[0]);
}

void sendWithWrite(STM32SPI& spi, uint8_t sendVal){
    
    auto val = spi.write(sendVal);

    printf("[Write Func] Send value : %d\n\r", sendVal);
    printf("[Write Func] Received value : %d\n\r", val);
}

void SpiSample_main(){
    STM32IotNode iotNode;
    STM32SPI spi( iotNode.io.miso, iotNode.io.mosi, iotNode.io.sclk, 1400000 ); // 1400000 Hz => 1.4 MHz

    iotNode.serial.init( 115200 );

    printf("\n");
    printf("*******************************************\n\r");
    printf("*  Demonstration de la communication SPI  *\n\r");
    printf("*******************************************\n\r");

    bool state = false;
    uint8_t sendVal = 0;

    while(true) {
        sendWithTransaction(spi, sendVal);
        sendWithWrite(spi, sendVal);
        printf("\n\r");

        iotNode.io.led2.setDigitalValue(state ? 1 : 0);
        state = !state;
        sendVal++;

        iotNode.sleep(2000);
    }
}