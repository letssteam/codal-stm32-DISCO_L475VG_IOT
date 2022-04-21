#include "PWMSample.h"

using namespace codal;

void setPWM(codal::STM32DISCO_L475VG_IOT& discoL475VgIot, uint16_t pwmValue)
{
    discoL475VgIot.io.D0.setAnalogValue(pwmValue);
    discoL475VgIot.io.D1.setAnalogValue(pwmValue);
    discoL475VgIot.io.D2.setAnalogValue(pwmValue);
    discoL475VgIot.io.D3.setAnalogValue(pwmValue);
    discoL475VgIot.io.D4.setAnalogValue(pwmValue);
    discoL475VgIot.io.D5.setAnalogValue(pwmValue);
    discoL475VgIot.io.D6.setAnalogValue(pwmValue);
    discoL475VgIot.io.D9.setAnalogValue(pwmValue);
    discoL475VgIot.io.D10.setAnalogValue(pwmValue);
    discoL475VgIot.io.D11.setAnalogValue(pwmValue);
}

void PWMSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    while (true) {
        for (uint16_t i = 0; i < 1024; ++i) {
            setPWM(discoL475VgIot, i);
            discoL475VgIot.sleep(1);
        }

        for (uint16_t i = 0; i < 1024; ++i) {
            setPWM(discoL475VgIot, 1023 - i);
            discoL475VgIot.sleep(1);
        }
    }
}
