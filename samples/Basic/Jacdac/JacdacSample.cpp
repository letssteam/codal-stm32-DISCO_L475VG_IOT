#include "JacdacSample.h"

#include "CodalJacdac.h"
#include "STM32SingleWireSerial.h"

using namespace codal;
void JacdacSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    auto sws    = STM32SingleWireSerial(discoL475VgIot.io.D2);
    auto jacdac = CodalJacdac::getInstance(&sws);

    while (true) {
        discoL475VgIot.io.led1.setDigitalValue(1);
        discoL475VgIot.sleep(250);
        discoL475VgIot.io.led1.setDigitalValue(0);
        discoL475VgIot.sleep(250);
    }
}
