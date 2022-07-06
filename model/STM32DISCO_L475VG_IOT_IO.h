#pragma once

#include "STM32Pin.h"
//
// Component IDs for each pin.
// The can be user defined, but uniquely identify a pin when using the eventing APIs/
//
#define ID_PIN_P0                               (DEVICE_ID_IO_P0 + 0)
#define ID_PIN_P1                               (DEVICE_ID_IO_P0 + 1)
#define ID_PIN_P2                               (DEVICE_ID_IO_P0 + 2)
#define ID_PIN_P3                               (DEVICE_ID_IO_P0 + 3)
#define ID_PIN_P4                               (DEVICE_ID_IO_P0 + 4)
#define ID_PIN_P5                               (DEVICE_ID_IO_P0 + 5)
#define ID_PIN_P6                               (DEVICE_ID_IO_P0 + 6)
#define ID_PIN_P7                               (DEVICE_ID_IO_P0 + 7)
#define ID_PIN_P8                               (DEVICE_ID_IO_P0 + 8)
#define ID_PIN_P9                               (DEVICE_ID_IO_P0 + 9)
#define ID_PIN_P10                              (DEVICE_ID_IO_P0 + 10)
#define ID_PIN_P11                              (DEVICE_ID_IO_P0 + 11)
#define ID_PIN_P12                              (DEVICE_ID_IO_P0 + 12)
#define ID_PIN_P13                              (DEVICE_ID_IO_P0 + 13)
#define ID_PIN_P14                              (DEVICE_ID_IO_P0 + 14)
#define ID_PIN_P15                              (DEVICE_ID_IO_P0 + 15)
#define ID_PIN_P16                              (DEVICE_ID_IO_P0 + 16)
#define ID_PIN_P17                              (DEVICE_ID_IO_P0 + 17)
#define ID_PIN_P18                              (DEVICE_ID_IO_P0 + 18)
#define ID_PIN_P19                              (DEVICE_ID_IO_P0 + 19)
#define ID_PIN_P20                              (DEVICE_ID_IO_P0 + 20)
#define ID_PIN_P21                              (DEVICE_ID_IO_P0 + 21)
#define ID_PIN_P22                              (DEVICE_ID_IO_P0 + 22)
#define ID_PIN_P23                              (DEVICE_ID_IO_P0 + 23)
#define ID_PIN_P24                              (DEVICE_ID_IO_P0 + 24)
#define ID_PIN_P25                              (DEVICE_ID_IO_P0 + 25)
#define ID_PIN_P26                              (DEVICE_ID_IO_P0 + 26)
#define ID_PIN_P27                              (DEVICE_ID_IO_P0 + 27)
#define ID_PIN_P28                              (DEVICE_ID_IO_P0 + 28)
#define ID_PIN_P29                              (DEVICE_ID_IO_P0 + 29)
#define ID_PIN_P30                              (DEVICE_ID_IO_P0 + 30)
#define ID_PIN_P31                              (DEVICE_ID_IO_P0 + 31)
#define ID_PIN_SDA                              (DEVICE_ID_IO_P0 + 32)
#define ID_PIN_SCL                              (DEVICE_ID_IO_P0 + 33)
#define ID_PIN_MISO                             (DEVICE_ID_IO_P0 + 34)
#define ID_PIN_MOSI                             (DEVICE_ID_IO_P0 + 35)
#define ID_PIN_SCLK                             (DEVICE_ID_IO_P0 + 36)
#define ID_PIN_CS                               (DEVICE_ID_IO_P0 + 37)
#define ID_PIN_BLE_MISO                         (DEVICE_ID_IO_P0 + 38)
#define ID_PIN_BLE_MOSI                         (DEVICE_ID_IO_P0 + 39)
#define ID_PIN_BLE_SCLK                         (DEVICE_ID_IO_P0 + 40)
#define ID_PIN_BLE_CS                           (DEVICE_ID_IO_P0 + 41)
#define ID_PIN_BLE_RST                          (DEVICE_ID_IO_P0 + 42)
#define ID_PIN_BLE_IRQ                          (DEVICE_ID_IO_P0 + 43)
#define ID_PIN_RX                               (DEVICE_ID_IO_P0 + 44)
#define ID_PIN_TX                               (DEVICE_ID_IO_P0 + 45)
#define ID_PIN_WIFI_ISM43362_WAKE_UP            (DEVICE_ID_IO_P0 + 46)
#define ID_PIN_WIFI_ISM43362_RESET              (DEVICE_ID_IO_P0 + 47)
#define ID_PIN_WIFI_ISM43362_CS                 (DEVICE_ID_IO_P0 + 48)
#define ID_PIN_WIFI_ISM43362_MISO               (DEVICE_ID_IO_P0 + 38)
#define ID_PIN_WIFI_ISM43362_MOSI               (DEVICE_ID_IO_P0 + 39)
#define ID_PIN_WIFI_ISM43362_SCK                (DEVICE_ID_IO_P0 + 40)
#define ID_PIN_WIFI_ISM43362_COMMAND_DATA_READY (DEVICE_ID_IO_P0 + 41)

namespace codal {
/**
 * Represents a collection of all I/O pins exposed by the device.
 */
class STM32DISCO_L475VG_IOT_IO {
  public:
    /**
     * Constructor.
     */
    STM32DISCO_L475VG_IOT_IO();

    STM32Pin A0;
    STM32Pin A1;
    STM32Pin A2;
    STM32Pin A3;
    STM32Pin A4;
    STM32Pin A5;

    STM32Pin D0;
    STM32Pin D1;
    STM32Pin D2;
    STM32Pin D3;
    STM32Pin D4;
    STM32Pin D5;
    STM32Pin D6;
    STM32Pin D7;
    STM32Pin D8;
    STM32Pin D9;
    STM32Pin D10;
    STM32Pin D11;
    STM32Pin D12;
    STM32Pin D13;
    STM32Pin D14;
    STM32Pin D15;

    STM32Pin led1;
    STM32Pin led2;
    STM32Pin led3;

    STM32Pin btnUser;

    STM32Pin miso;
    STM32Pin mosi;
    STM32Pin sclk;

    STM32Pin miso3;
    STM32Pin mosi3;
    STM32Pin sclk3;

    STM32Pin sda;
    STM32Pin scl;

    STM32Pin sda2;
    STM32Pin scl2;

    STM32Pin tx;
    STM32Pin rx;

    STM32Pin pc6;
    STM32Pin pc7;

    STM32Pin bleCS;
    STM32Pin bleIRQ;
    STM32Pin bleRST;
};
}  // namespace codal
