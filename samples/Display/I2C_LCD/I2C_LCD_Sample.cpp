#include "I2C_LCD_Sample.h"

void i2cLCDSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    codal::I2C_LCD lcd(discoL475VgIot.i2c1);
    lcd.init();
    lcd.backlightOn();
    lcd.blinkOn();
    lcd.cursorOn();

    while (true) {
        lcd.clear();
        lcd.print("Hello");
        discoL475VgIot.sleep(1000);

        lcd.setCursor(5, 1);
        lcd.print("World !");
        discoL475VgIot.sleep(1000);

        lcd.clear();
        lcd.print("10 in BIN");
        lcd.setCursor(0, 1);
        lcd.print(10, PrintRadix::BIN);
        discoL475VgIot.sleep(1000);

        lcd.clear();
        lcd.print("10 in HEX");
        lcd.setCursor(0, 1);
        lcd.print(10, PrintRadix::HEX);
        discoL475VgIot.sleep(1000);

        lcd.clear();
        lcd.print("10 in OCT");
        lcd.setCursor(0, 1);
        lcd.print(10, PrintRadix::OCT);
        discoL475VgIot.sleep(1000);

        lcd.clear();
        lcd.print("10 in DEC");
        lcd.setCursor(0, 1);
        lcd.print(10, PrintRadix::DEC);
        discoL475VgIot.sleep(1000);

        lcd.clear();
        lcd.print("123.456789");
        lcd.setCursor(0, 1);
        lcd.print(123.456789, 2);
        discoL475VgIot.sleep(1000);

        lcd.clear();
        lcd.print("123.456789");
        lcd.setCursor(0, 1);
        lcd.print(123.456789, 6);
        discoL475VgIot.sleep(1000);
    }
}
