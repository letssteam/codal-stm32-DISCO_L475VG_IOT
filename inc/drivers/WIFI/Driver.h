#pragma once

#include "STM32Pin.h"

class Driver {
  protected:
    codal::STM32Pin* resetPin;
    codal::STM32Pin* wakeUpPin;

  public:
    Driver(codal::STM32Pin* resetPin, codal::STM32Pin* wakeUpPin) : resetPin(resetPin), wakeUpPin(wakeUpPin) {}
    virtual ~Driver() {}
    virtual int8_t IO_Init(void)                                 = 0;
    virtual void IO_DeInit(void)                                 = 0;
    virtual void IO_Delay(uint32_t)                              = 0;
    virtual int16_t IO_Send(uint8_t*, uint16_t len, uint32_t)    = 0;
    virtual int16_t IO_Receive(uint8_t*, uint16_t len, uint32_t) = 0;
};
