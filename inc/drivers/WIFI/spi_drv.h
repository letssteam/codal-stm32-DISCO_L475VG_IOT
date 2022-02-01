#pragma once

#include <inttypes.h>

#include "STM32Pin.h"
#include "STM32SPI.h"
#include "driver.h"

#define MAX_TRY_INIT    100
#define MAX_SIZE_ANSWER 255

class SpiDrvClass : public DriverClass {
  private:
    codal::STM32SPI* ISM43362;
    // SPISettings *Settings_43362;
    codal::Pin* nssPin;
    codal::Pin* commandDataReadyPin;

  public:
    SpiDrvClass(codal::STM32SPI* SPIx, PinNumber cs, PinNumber commandDataReady, PinNumber reset, PinNumber wakeup);

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