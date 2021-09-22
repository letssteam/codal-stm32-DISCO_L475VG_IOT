#pragma once

#include "Event.h"
#include "STM32DISCO_L475VG_IOT.h"
#include "Timer.h"

#ifndef SAMPLE_MAIN
#define SAMPLE_MAIN MessageBusSample_main
#endif

void MessageBusSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot);

void update_function(codal::Event evt, void* ctx);

class SampleMessageBus {
  private:
    const int ID         = 3000;
    const int EVENT_TYPE = 1;

    void update(codal::Event evt)
    {
        (void)evt;
        state = !state;
    }

  public:
    bool state;

    SampleMessageBus(codal::STM32DISCO_L475VG_IOT& discoL475VgIot) : state(false)
    {
        if (codal::EventModel::defaultEventBus) {
            auto result = codal::EventModel::defaultEventBus->listen(ID, EVENT_TYPE, this, &SampleMessageBus::update,
                                                                     MESSAGE_BUS_LISTENER_IMMEDIATE);
            // auto result = codal::EventModel::defaultEventBus->listen(ID, EVENT_TYPE, &update_function, this,
            //                                                          MESSAGE_BUS_LISTENER_IMMEDIATE);

            if (result == DEVICE_INVALID_PARAMETER) {
                while (1) {
                    discoL475VgIot.io.led1.setDigitalValue(discoL475VgIot.io.led1.getDigitalValue() ? 0 : 1);
                    discoL475VgIot.io.led2.setDigitalValue(discoL475VgIot.io.led2.getDigitalValue() ? 0 : 1);
                    discoL475VgIot.sleep(100);
                }
            }
        }

        codal::system_timer_event_every(500, ID, EVENT_TYPE);
    }
};
