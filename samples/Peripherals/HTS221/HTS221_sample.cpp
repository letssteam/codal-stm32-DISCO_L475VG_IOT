
#include "HTS221_sample.h"

using namespace codal;
using namespace std;

void hts221Sample(){

    STM32IotNode iotNode;
    SSD1306_I2C oled( iotNode.i2c1, 0x78, 128, 64, false );
    HTS221 hts( iotNode.i2c2, 0xBE );


    oled.init();
    hts.init();

    hts.setOutputRate( HTS221_OUTPUT_RATE::RATE_1HZ );

    oled.fill(0);
    oled.drawText( "HTS221 test !!", 29, 36, 1 );
    oled.show();

    iotNode.sleep( 2000 );

    string tempStr;
    string humStr;

    while(true){

        oled.fill(0);
        
        while( ! hts.isTemperatureDataAvailable() || ! hts.isHumidityDataAvailable() ){
            iotNode.sleep(10);
        }

        tempStr = "Temp : " + to_string( hts.getTemperature() ).substr(0, 5) + " C";
        humStr  = "Hum : " + to_string( hts.getHumidity() ).substr(0, 5) + " %RH";

        oled.drawText( "HTS221 test", 28, 0, 1 );
        oled.drawText( tempStr, 0, 30, 1 );
        oled.drawText( humStr, 0, 38, 1 );

        oled.show();
        iotNode.sleep(500);
    }

}