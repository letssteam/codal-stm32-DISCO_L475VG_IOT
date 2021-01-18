#include "OLED_SSD1306.h"

#include "i2c.h"
#include "pinmap.h"

using namespace codal;


void HelloWorld( SSD1306& oled ){

    oled.fill(1);
    oled.drawText("Hello World !", 0, 0, 0);
    oled.drawText("<3", 0, 8, 0);
    oled.show();
}

void CharScreen( SSD1306& oled ){
    oled.fill(1);

    for( int y = 0; y < 8; ++y ){
        for( int x = 0; x < 16; ++x){
            oled.drawChar( char(x + y * 16), x * 8, y * 8, 0 );
        }
    }

    oled.show();
}

void BlinkScreen(STM32IotNode& iotNode,  SSD1306& oled, uint32_t delay){
    oled.invert(0);
    iotNode.sleep(delay);
    oled.invert(1);
    iotNode.sleep(delay);
    oled.invert(0);
    iotNode.sleep(delay);
    oled.invert(1);
    iotNode.sleep(delay);
}


void OledSample(){

    STM32IotNode iotNode;

    SSD1306_I2C oled( iotNode.i2c1, 0x78, 128, 64, false );

    oled.init();

    uint8_t state = 0;
    uint8_t count = 0;

	while(1)
    {    
        HelloWorld(oled);
        BlinkScreen(iotNode, oled, 500);
        CharScreen(oled);
        BlinkScreen(iotNode, oled, 1000);
    }
}