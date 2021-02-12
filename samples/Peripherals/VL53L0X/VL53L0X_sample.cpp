
#include "VL53L0X_sample.h"

using namespace codal;
using namespace std;

void vlx53l0xSample(){

    STM32IotNode iotNode;
    SSD1306_I2C oled( iotNode.i2c1, 0x78, 128, 64, false );
    VL53L0X vl( iotNode.i2c2,  iotNode.io.pc6, 0x52 );


    oled.init();
    vl.init();

    oled.fill(0);
    oled.drawText( "VL53L0X test !!", 24, 36, 1 );
    oled.show();

    iotNode.sleep( 2000 );

    string dist;

    while(true){

        oled.fill(0);

        dist = "Dist : " + to_string( vl.getDistance() ) + " mm";

        oled.drawText( "VL53L0x test", 24, 0, 1 );
        oled.drawText( dist, 0, 30, 1 );

        oled.show();
        iotNode.sleep(500);
    }

}