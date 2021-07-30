#include "OLED_SSD1306.h"

#include "pinmap.h"
#include "wiring_time.h"

void HelloWorld(codal::SSD1306* oled)
{
    oled->fill(1);
    oled->drawText("Hello World !", 0, 0, 0);
    oled->drawText("<3", 0, 8, 0);
    oled->show();
}

void CharScreen(codal::SSD1306* oled)
{
    oled->fill(1);

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 16; ++x) {
            oled->drawChar(char(x + y * 16), x * 8, y * 8, 0);
        }
    }

    oled->show();
}

void BlinkScreen(codal::SSD1306* oled, uint32_t ms)
{
    oled->invert(false);
    delay(ms);
    oled->invert(true);
    delay(ms);
    oled->invert(false);
    delay(ms);
    oled->invert(true);
    delay(ms);
}

void OledSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    codal::SSD1306_I2C oled(discoL475VgIot.i2c1, 0x78, 128, 64, false);

    oled.init();

    while (true) {
        HelloWorld(&oled);
        BlinkScreen(&oled, 500);
        CharScreen(&oled);
        BlinkScreen(&oled, 1000);
    }
}
