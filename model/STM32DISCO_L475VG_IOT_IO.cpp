/*
The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

/**
 * Class definition for STM32 IOT node IO.
 * Represents a collection of all I/O pins on the device.
 */

#include "STM32DISCO_L475VG_IOT_IO.h"

using codal::STM32DISCO_L475VG_IOT_IO;

/**
 * Constructor.
 *
 * Create a representation of all given I/O pins on the connectors
 *
 * Accepts a sequence of unique ID's used to distinguish events raised
 * by Pin instances on the default EventModel.
 */
STM32DISCO_L475VG_IOT_IO::STM32DISCO_L475VG_IOT_IO()
    : A0(ID_PIN_P0, PinNumber::PC_5, PIN_CAPABILITY_AD),
      A1(ID_PIN_P1, PinNumber::PC_4, PIN_CAPABILITY_AD),
      A2(ID_PIN_P2, PinNumber::PC_3, PIN_CAPABILITY_AD),
      A3(ID_PIN_P3, PinNumber::PC_2, PIN_CAPABILITY_AD),
      A4(ID_PIN_P4, PinNumber::PC_1, PIN_CAPABILITY_AD),
      A5(ID_PIN_P5, PinNumber::PC_0, PIN_CAPABILITY_AD),
      D0(ID_PIN_P6, PinNumber::PA_1, PIN_CAPABILITY_AD),
      D1(ID_PIN_P7, PinNumber::PA_0, PIN_CAPABILITY_AD),
      D2(ID_PIN_P8, PinNumber::PD_14, PIN_CAPABILITY_AD),
      D3(ID_PIN_P9, PinNumber::PB_0_ALT1, PIN_CAPABILITY_AD),
      D4(ID_PIN_P10, PinNumber::PA_3, PIN_CAPABILITY_AD),
      D5(ID_PIN_P11, PinNumber::PB_4, PIN_CAPABILITY_AD),
      D6(ID_PIN_P12, PinNumber::PB_1_ALT1, PIN_CAPABILITY_AD),
      D7(ID_PIN_P13, PinNumber::PA_4, PIN_CAPABILITY_AD),
      D8(ID_PIN_P14, PinNumber::PB_2, PIN_CAPABILITY_AD),
      D9(ID_PIN_P15, PinNumber::PA_15, PIN_CAPABILITY_AD),
      D10(ID_PIN_P16, PinNumber::PA_2, PIN_CAPABILITY_AD),
      D11(ID_PIN_P17, PinNumber::PA_7_ALT1, PIN_CAPABILITY_AD),
      D12(ID_PIN_P18, PinNumber::PA_6, PIN_CAPABILITY_AD),
      D13(ID_PIN_P19, PinNumber::PA_5, PIN_CAPABILITY_AD),
      D14(ID_PIN_P20, PinNumber::PB_9, PIN_CAPABILITY_AD),
      D15(ID_PIN_P21, PinNumber::PB_8, PIN_CAPABILITY_AD),

      led1(ID_PIN_P19, PinNumber::PA_5, PIN_CAPABILITY_AD),
      led2(ID_PIN_P22, PinNumber::PB_14, PIN_CAPABILITY_AD),
      led3(ID_PIN_P22, PinNumber::PC_9, PIN_CAPABILITY_AD),

      btnUser(DEVICE_ID_BUTTON_A, PinNumber::PC_13, PIN_CAPABILITY_DIGITAL),

      miso(ID_PIN_MISO, PinNumber::PA_6, PIN_CAPABILITY_DIGITAL),
      mosi(ID_PIN_MOSI, PinNumber::PA_7, PIN_CAPABILITY_DIGITAL),
      sclk(ID_PIN_SCLK, PinNumber::PA_5, PIN_CAPABILITY_DIGITAL),

      miso3(ID_PIN_MISO, PinNumber::PC_11, PIN_CAPABILITY_DIGITAL),
      mosi3(ID_PIN_MOSI, PinNumber::PC_12, PIN_CAPABILITY_DIGITAL),
      sclk3(ID_PIN_SCLK, PinNumber::PC_10, PIN_CAPABILITY_DIGITAL),

      sda(ID_PIN_SDA, PinNumber::PB_9, PIN_CAPABILITY_DIGITAL),
      scl(ID_PIN_SCL, PinNumber::PB_8, PIN_CAPABILITY_DIGITAL),

      sda2(ID_PIN_SDA, PinNumber::PB_11, PIN_CAPABILITY_DIGITAL),
      scl2(ID_PIN_SCL, PinNumber::PB_10, PIN_CAPABILITY_DIGITAL),

      tx(ID_PIN_RX, PinNumber::PB_6, PIN_CAPABILITY_DIGITAL),
      rx(ID_PIN_TX, PinNumber::PB_7, PIN_CAPABILITY_DIGITAL),
      pc6(ID_PIN_P23, PinNumber::PC_6, PIN_CAPABILITY_DIGITAL),
      pc7(ID_PIN_P24, PinNumber::PC_7, PIN_CAPABILITY_DIGITAL),

      bleCS(ID_PIN_BLE_CS, PinNumber::PD_13, PIN_CAPABILITY_AD),
      bleIRQ(ID_PIN_BLE_IRQ, PinNumber::PE_6, PIN_CAPABILITY_AD),
      bleRST(ID_PIN_BLE_RST, PinNumber::PA_8, PIN_CAPABILITY_AD)
{
}
