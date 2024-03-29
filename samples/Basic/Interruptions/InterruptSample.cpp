#include "InterruptSample.h"

#include "Event.h"
#include "EventModel.h"
#include "STM32Pin.h"
#include "interrupt.h"

codal::STM32Pin* led;

void toggleLed(codal::Event e)
{
    switch (e.value) {
        case DEVICE_PIN_EVT_FALL:
            led->setDigitalValue(1);
            break;
        case DEVICE_PIN_EVT_RISE:
            led->setDigitalValue(0);
            break;
        default:
            return;
    }
}

void InterruptSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    codal::STM32Pin& userBtn = discoL475VgIot.io.btnUser;
    led                      = &discoL475VgIot.io.led1;
    led->setDigitalValue(0);
    discoL475VgIot.io.btnUser.eventOn(DEVICE_PIN_EVENT_ON_EDGE);
    codal::EventModel::defaultEventBus->listen(userBtn.id, DEVICE_PIN_EVT_RISE, &toggleLed,
                                               MESSAGE_BUS_LISTENER_IMMEDIATE);
    codal::EventModel::defaultEventBus->listen(userBtn.id, DEVICE_PIN_EVT_FALL, &toggleLed,
                                               MESSAGE_BUS_LISTENER_IMMEDIATE);

    while (true) {
        discoL475VgIot.sleep(1000);
    }
}