# Codal target for the DISCO_L475VG_IOT Board [![codal-stm32-DISCO_L475VG_IOT](https://img.shields.io/github/workflow/status/letssteam/codal-stm32-DISCO_L475VG_IOT/codal-buildtarget?label=codal-stm32-DISCO_L475VG_IOT)](https://github.com/letssteam/codal-stm32-DISCO_L475VG_IOT/actions)

Codal target for the [B-L475E-IOT01A](http://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) Discovery kit for IoT node. Codal is the core set of drivers, mechanisms and types that make up the runtime for a board in Makecode.

## Overview

The codal runtime provides an easy to use environment for programming the board in the C/C++ language, written by Lancaster University. It contains device drivers for all the hardware capabilities, and also a suite of runtime mechanisms to make programming the easier and more flexible. These range from control of the LED matrix display to peer-to-peer radio communication and secure Bluetooth Low Energy services.

In addition to supporting development in C/C++, the runtime is also designed specifically to support higher level languages provided by our partners that target physical computing and computer science education. It is currently used as a support library for Microsoft MakeCode

Codal-core must be implemented by third party developper to support new hardware target. This repository constain the codal implementation for the [B-L475E-IOT01A](http://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) Discovery kit for IoT node.

## Board Information  

The [B-L475E-IOT01A](http://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) Discovery kit for IoT node allows users to develop applications with direct connection to cloud servers.

The Discovery kit enables a wide diversity of applications by exploiting low-power communication, multiway sensing and Arm® Cortex® -M4 core-based STM32L4 Series features.

The support for Arduino Uno V3 and PMOD connectivity provides unlimited expansion capabilities with a large choice of specialized add-on boards.

<img src="https://pxt.azureedge.net/blob/7490df2fec08171c631b815eac97dae0dae5a8a0//static/boards/stm32-iot-node/board.simplified.svg" width="600px" />

## Feature List (and if implemented in codal)

- [ ] 64-Mbit Quad-SPI (Macronix) Flash memory
- [ ] Bluetooth® V4.1 module (SPBTLE-RF)
- [ ] Sub-GHz (868 or 915 MHz) low-power-programmable RF module (SPSGRF-868 or SPSGRF-915)
- [ ] Wi-Fi® module Inventek ISM43362-M3G-L44 (802.11 b/g/n compliant)
- [ ] Dynamic NFC tag based on M24SR with its printed NFC antenna
- [ ] 2 digital omnidirectional microphones (MP34DT01)
- [ ] USB OTG FS
- [ ] Capacitive digital sensor for relative humidity and temperature (HTS221)
- [ ] High-performance 3-axis magnetometer (LIS3MDL)
- [ ] 3D accelerometer and 3D gyroscope (LSM6DSL)
  - [ ] 3D Accelerometer (Complete)
  - [ ] 3D Gyroscope (Complete)
- [ ] 260-1260 hPa absolute digital output barometer (LPS22HB)
- [ ] Time-of-Flight and gesture-detection sensor (VL53L0X)
- [ ] 2 push-buttons (user and reset)
- [ ] GPIO
- [ ] ADC 12 bits
- [ ] FAT Storage over the flash memory
- [ ] Expansion connectors:
  - [ ] Arduino™ Uno V3
  - [ ] PMOD

## Installation

Before using this target you need to configure your platforms with some software.
Codal is also a build system to simplify as much as possible the experience of novice users.  

1. Install `git`, ensure it is available on your platforms path.
2. Install the `arm-none-eabi-*` command line utilities for ARM based devices, ensure they are available on your platforms path.
3. Install [CMake](https://cmake.org)(Cross platform make), this is the entirety of the build system.
4. Install `Python 2.7` (if you are unfamiliar with CMake), python scripts are used to simplify the build process.
5. Clone the repository <https://github.com/lancaster-university/codal>

## Building

- Create a `codal.json` file :
  ```json
  {
    "target": {
        "name": "codal-stm32-DISCO_L475VG_IOT", 
        "url": "https://github.com/letssteam/codal-stm32-DISCO_L475VG_IOT", 
        "branch": "master", 
        "type": "git", 
        "test_ignore": true
    }
  }
  ```
- In the root of this repository type `python build.py` the `-c` option cleans before building.
- The bin file `STM32_IOT_NODE.bin` will be placed at the location specified by `codal.json`, by default this is the root.
- To test the sample program, you just copy the bin file in the mass storage of the board.

### Advanced use

If you would like to override or define any additional configuration options (`#define's`) that are used by the supporting libraries, the codal build system allows the addition of a config field in `codal.json`:

```json
{
    "target": {
        "name": "codal-stm32-DISCO_L475VG_IOT", 
        "url": "https://github.com/letssteam/codal-stm32-DISCO_L475VG_IOT", 
        "branch": "master", 
        "type": "git", 
        "test_ignore": true
    },
    "config":{
        "NUMBER_ONE":1
    },
    "application":"source",
    "output_folder":"."
}
```

The above example will be translate `"NUMBER_ONE":1` into: `#define NUMBER_ONE     1` and force include it during compilation. You can also specify alternate application or output folders.

#### Execute a specific sample application

By default, the application present in the `source` directory is the content of the `samples` directory of this repository. Since you can just execute one example at the time, you need to configure your target to specify the one you want.

For example, if you want to test the `BLE_TEMPERATURE_ALARM_SAMPLE`, you need to configure the corresponding `#define` with the following `codal.json`:

```json
{
    "target": {
        "name": "codal-stm32-DISCO_L475VG_IOT", 
        "url": "https://github.com/letssteam/codal-stm32-DISCO_L475VG_IOT", 
        "branch": "master", 
        "type": "git", 
        "test_ignore": true
    },
    "config":{
        "BLE_TEMPERATURE_ALARM_SAMPLE":1
    },
    "application":"source",
    "output_folder":"."
}
```
