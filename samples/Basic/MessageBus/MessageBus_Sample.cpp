#include "MessageBus_Sample.h"

using namespace codal;

SampleMessageBus* sample;

void MessageBusSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    sample = new SampleMessageBus(discoL475VgIot);

    while (true) {
        discoL475VgIot.io.led1.setDigitalValue(sample->state ? 1 : 0);
        discoL475VgIot.io.led2.setDigitalValue(discoL475VgIot.io.led2.getDigitalValue() ? 0 : 1);
        discoL475VgIot.sleep(250);
    }
}
