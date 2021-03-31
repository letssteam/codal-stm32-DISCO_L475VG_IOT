
#include "LPS22HB_sample.h"

using namespace codal;
using namespace std;

void lps22hbSample()
{
    STM32IotNode iotNode;
    iotNode.init();

    SSD1306_I2C oled(iotNode.i2c1, 0x78, 128, 64, false);
    LPS22HB lps(iotNode.i2c2, 0xBA);

    oled.init();
    lps.init();

    oled.fill(0);
    oled.drawText("LPS22HB Test !!", 16, 28, 1);
    oled.show();

    codal::STM32IotNode::sleep(2000);

    string pres;
    string temp;

    while (true) {
        pres = to_string(lps.getPressure()).substr(0, 6);
        temp = to_string(lps.getTemperature()).substr(0, 4);

        oled.fill(0);
        oled.drawText("LPS22HB", 38, 0, 1);
        oled.drawText("Pres : " + pres + "hPa", 0, 28, 1);
        oled.drawText("Temp : " + temp + " C", 0, 36, 1);
        oled.show();

        codal::STM32IotNode::sleep(500);
    }
}
