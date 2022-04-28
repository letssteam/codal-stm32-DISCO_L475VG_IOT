#include "joystick_sample.h"

#include "OLED_SSD1306.h"
#include "joystick.h"
#include "string.h"

std::string direction = "";
std::string button    = "";
void afficherLeft()
{
    direction = "left";
}
void afficherRight()
{
    direction = "right";
}
void afficherTop()
{
    direction = "top";
}
void afficherBottom()
{
    direction = "bottom";
}

void afficherClick()
{
    button = "clic";
}
void afficherLongClick()
{
    button = "clic long";
}
void afficherUp()
{
    button = "relachement";
}
void afficherDown()
{
    button = "appui";
}
void afficherHold()
{
    button = "maintien";
}
void afficherDoubleClick()
{
    button = "clic double";
}
void joystickSample(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    codal::SSD1306_I2C oled(&discoL475VgIot.i2c1, 0x78, 128, 64, false);
    oled.init();
    codal::Joystick* js = new codal::Joystick(discoL475VgIot.io.A0, discoL475VgIot.io.A1, discoL475VgIot.io.D2);

    js->registerDirectionEvent(codal::JoystickDirection::Left, afficherLeft);
    js->registerDirectionEvent(codal::JoystickDirection::Top, afficherTop);
    js->registerDirectionEvent(codal::JoystickDirection::Right, afficherRight);
    js->registerDirectionEvent(codal::JoystickDirection::Bottom, afficherBottom);

    js->registerButtonEvent(codal::ButtonEvent::Click, afficherClick);
    js->registerButtonEvent(codal::ButtonEvent::LongClick, afficherLongClick);
    js->registerButtonEvent(codal::ButtonEvent::Up, afficherUp);
    js->registerButtonEvent(codal::ButtonEvent::Down, afficherDown);
    js->registerButtonEvent(codal::ButtonEvent::Hold, afficherHold);

    while (true) {
        oled.fill(0);
        oled.drawText("h:", 0, 0, 1);
        oled.drawText(std::to_string(js->getAxis(codal::JoystickAxis::Horizontal)), 32, 0, 1);
        oled.drawText("v:", 64, 0, 1);
        oled.drawText(std::to_string(js->getAxis(codal::JoystickAxis::Vertical)), 96, 0, 1);
        oled.drawText("left:", 0, 9, 1);
        oled.drawText(std::to_string(js->isJoystickPointingTo(codal::JoystickDirection::Left)), 32, 9, 1);
        oled.drawText("right:", 64, 9, 1);
        oled.drawText(std::to_string(js->isJoystickPointingTo(codal::JoystickDirection::Right)), 104, 10, 1);
        oled.drawText("top:", 0, 18, 1);
        oled.drawText(std::to_string(js->isJoystickPointingTo(codal::JoystickDirection::Top)), 32, 18, 1);
        oled.drawText("bottom:", 64, 18, 1);
        oled.drawText(std::to_string(js->isJoystickPointingTo(codal::JoystickDirection::Bottom)), 112, 18, 1);
        oled.drawText("event joystick:", 0, 27, 1);
        oled.drawText(direction, 0, 36, 1);
        oled.drawText("event bouton:", 0, 45, 1);
        oled.drawText(button, 0, 54, 1);
        oled.show();
        discoL475VgIot.sleep(5);
    }
}