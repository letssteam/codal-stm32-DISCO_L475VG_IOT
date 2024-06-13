#pragma once

#include <inttypes.h>

#include "Driver.h"
#include "STM32Pin.h"
#include "STM32SPI.h"

#define MAX_TRY_INIT    100
#define MAX_SIZE_ANSWER 255

class SpiDriver : public Driver {
  private:
    codal::STM32SPI* ISM43362;
    codal::STM32Pin* csPin;
    codal::STM32Pin* commandDataReadyPin;

  public:
    SpiDriver(codal::STM32SPI* SPIx, codal::STM32Pin* csPin, codal::STM32Pin* commandDataReadyPin,
              codal::STM32Pin* resetPin, codal::STM32Pin* wakeupPin);

    void Spi_Wifi_Reset();
    void Spi_Slave_Select();
    void Spi_Slave_Deselect();
    uint8_t Spi_Get_Data_Ready_State();

    virtual int8_t IO_Init(void);
    virtual void IO_DeInit(void);
    virtual void IO_Delay(uint32_t time);
    virtual int16_t IO_Send(uint8_t* data, uint16_t len, uint32_t timeout);
    virtual int16_t IO_Receive(uint8_t* data, uint16_t len, uint32_t timeout);
};