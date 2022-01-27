/**
 ******************************************************************************
 * @file    es_wifi_io.c
 * @author  MCD Application Team
 * @brief   This file implements the IO operations to deal with the es-wifi
 *          module. It mainly Inits and Deinits the SPI interface. Send and
 *          receive data over it.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "es_wifi_io.h"

#include <core_cm4.h>
#include <string.h>

#include "STM32DISCO_L475VG_IOT_IO.h"
#include "STM32Pin.h"
#include "STM32SPI.h"
#include "WInterrupts.h"
#include "es_wifi.h"
#include "es_wifi_conf.h"
#include "pins_arduino.h"
#include "wiring_constants.h"

/* Private define ------------------------------------------------------------*/
#define MIN(a, b) ((a) < (b) ? (a) : (b))
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

codal::STM32Pin wakeUpPin(ID_PIN_WIFI_WAKE_UP, PinNumber::PB_13, codal::PIN_CAPABILITY_DIGITAL);
codal::STM32Pin resetPin(ID_PIN_WIFI_RESET, PinNumber::PE_8, codal::PIN_CAPABILITY_DIGITAL);
codal::STM32Pin nssPin(ID_PIN_WIFI_NSS, PinNumber::PE_0, codal::PIN_CAPABILITY_DIGITAL);
codal::STM32Pin commandDataReadyPin(ID_PIN_WIFI_COMMAND_DATA_READY, PinNumber::PE_1, codal::PIN_CAPABILITY_DIGITAL);

codal::STM32Pin miso3(ID_PIN_WIFI_MISO, PinNumber::PC_11, codal::PIN_CAPABILITY_DIGITAL);
codal::STM32Pin mosi3(ID_PIN_WIFI_MOSI, PinNumber::PC_12, codal::PIN_CAPABILITY_DIGITAL);
codal::STM32Pin sclk3(ID_PIN_WIFI_SCLK, PinNumber::PC_10, codal::PIN_CAPABILITY_DIGITAL);

codal::STM32SPI spi3(miso3, mosi3, sclk3, 8000000UL, 0, true);

#define WIFI_MODULE_SPI_BUFFER_SIZE 128

uint8_t _rxbuff[WIFI_MODULE_SPI_BUFFER_SIZE];
uint16_t _read_index;
uint16_t _write_index;
uint16_t _write_index_initial;

bool avalaible()
{
    return (_read_index != _write_index);
}

int peek()
{
    int peek_val = -1;

    if (_read_index != _write_index) {
        peek_val = _rxbuff[_read_index];
    }

    return peek_val;
}

int read()
{
    int read_val = -1;

    if (_read_index != _write_index) {
        read_val = _rxbuff[_read_index];
        _read_index++;
        if (_read_index == _write_index) {
            /* Reset buffer index */
            _read_index  = 0;
            _write_index = 0;
        }
    }

    return read_val;
}

static int volatile cmddata_rdy_rising_event = 0;

/* Private function prototypes -----------------------------------------------*/
static int wait_cmddata_rdy_high(int timeout);
static int wait_cmddata_rdy_rising_event(int timeout);

static void SPI_WIFI_DelayUs(uint32_t);

int wait_cmddata_rdy_high(int timeout)
{
    uint32_t tickstart = HAL_GetTick();
    while (WIFI_IS_CMDDATA_READY() == 0) {
        if ((HAL_GetTick() - tickstart) > (uint32_t)timeout) {
            return -1;
        }
    }
    return 0;
}

int wait_cmddata_rdy_rising_event(int timeout)
{
    int tickstart = HAL_GetTick();
    while (!avalaible() && cmddata_rdy_rising_event == 1) {
        if ((HAL_GetTick() - tickstart) > (uint32_t)timeout) {
            return -1;
        }
    }
    return 0;
}

/**
 * @brief  Interrupt handler for  Data RDY signal
 * @param  None
 * @retval None
 */
extern "C" void SPI_WIFI_ISR(void)
{
    if (cmddata_rdy_rising_event == 1) {
        cmddata_rdy_rising_event = 0;
    }
}

/**
 * @brief  Initialize the Wifi module
 * @param  None
 * @retval None
 */
int8_t SPI_WIFI_Init(uint16_t mode)
{
    _read_index          = 0;
    _write_index         = 0;
    _write_index_initial = 0;
    memset(_rxbuff, 0, sizeof(_rxbuff));

    attachInterrupt(pinNametoDigitalPin(PE_1), SPI_WIFI_ISR, RISING);

    int8_t rc = 0;

    if (mode == ES_WIFI_INIT) {
        /* Enable Interrupt for Data Ready pin , GPIO_PIN1 */
        HAL_NVIC_SetPriority((IRQn_Type)EXTI1_IRQn, SPI_INTERFACE_PRIO, 0x00);
        HAL_NVIC_EnableIRQ((IRQn_Type)EXTI1_IRQn);

        /* Enable Interrupt for SPI tx and rx */
        HAL_NVIC_SetPriority((IRQn_Type)SPI3_IRQn, SPI_INTERFACE_PRIO, 0);
        HAL_NVIC_EnableIRQ((IRQn_Type)SPI3_IRQn);

        /* first call used for calibration */
        SPI_WIFI_DelayUs(10);
    }

    rc = SPI_WIFI_ResetModule();

    return rc;
}

int8_t SPI_WIFI_ResetModule(void)
{
    uint32_t tickstart = HAL_GetTick();
    uint8_t Prompt[6];
    uint8_t count = 0;

    WIFI_RESET_MODULE();

    LOCK_SPI();
    WIFI_ENABLE_NSS();

    SPI_WIFI_DelayUs(15);

    while (WIFI_IS_CMDDATA_READY()) {
        Prompt[count + 1] = spi3.write(0);
        Prompt[count]     = spi3.write(0);

        count += 2;
        if (((HAL_GetTick() - tickstart) > 0xFFFF)) {
            WIFI_DISABLE_NSS();
            return -1;
        }
    }

    WIFI_DISABLE_NSS();
    UNLOCK_SPI();

    if ((Prompt[0] != 0x15) || (Prompt[1] != 0x15) || (Prompt[2] != '\r') || (Prompt[3] != '\n') ||
        (Prompt[4] != '>') || (Prompt[5] != ' ')) {
        return -1;
    }
    return 0;
}

/**
 * @brief  DeInitialize the SPI
 * @param  None
 * @retval None
 */
int8_t SPI_WIFI_DeInit(void)
{
    detachInterrupt(pinNametoDigitalPin(PE_1));
    return 0;
}

/**
 * @brief  Receive wifi Data from SPI
 * @param  pdata : pointer to data
 * @param  len : Data length
 * @param  timeout : send timeout in mS
 * @retval Length of received data (payload)
 */
int16_t SPI_WIFI_ReceiveData(uint8_t* pData, uint16_t len, uint32_t timeout)
{
    int16_t length = 0;

    WIFI_DISABLE_NSS();
    UNLOCK_SPI();

    SPI_WIFI_DelayUs(15);

    if (wait_cmddata_rdy_rising_event(timeout) < 0) {
        return ES_WIFI_ERROR_WAITING_DRDY_FALLING;
    }

    while (avalaible()) {
        if ((length < len) || (!len)) {
            pData[0] = read();
            pData[1] = read();
            length += 2;
            pData += 2;

            if (length >= ES_WIFI_DATA_SIZE) {
                WIFI_DISABLE_NSS();
                SPI_WIFI_ResetModule();
                UNLOCK_SPI();
                return ES_WIFI_ERROR_STUFFING_FOREVER;
            }
        }
    }

    LOCK_SPI();
    WIFI_ENABLE_NSS();
    SPI_WIFI_DelayUs(15);

    while (WIFI_IS_CMDDATA_READY()) {
        if ((length < len) || (!len)) {
            pData[1] = spi3.write(0);
            pData[0] = spi3.write(0);
            length += 2;
            pData += 2;

            if (length >= ES_WIFI_DATA_SIZE) {
                WIFI_DISABLE_NSS();
                SPI_WIFI_ResetModule();
                UNLOCK_SPI();
                return ES_WIFI_ERROR_STUFFING_FOREVER;
            }
        }
        else {
            break;
        }
    }
    WIFI_DISABLE_NSS();
    UNLOCK_SPI();
    return length;
}
/**
 * @brief  Send wifi Data through SPI
 * @param  pdata : pointer to data
 * @param  len : Data length
 * @param  timeout : send timeout in mS
 * @retval Length of sent data
 */
int16_t SPI_WIFI_SendData(uint8_t* pdata, uint16_t len, uint32_t timeout)
{
    if (wait_cmddata_rdy_high(timeout) < 0) {
        return ES_WIFI_ERROR_SPI_FAILED;
    }

    /* arm to detect rising event */
    cmddata_rdy_rising_event = 1;
    LOCK_SPI();
    WIFI_ENABLE_NSS();
    SPI_WIFI_DelayUs(15);
    if (len > 1) {
        for (int i = 0; i < len; i += 2) {
            _rxbuff[_write_index + 1] = spi3.write(pdata[i + 1]);
            _rxbuff[_write_index]     = spi3.write(pdata[i]);
            _write_index += 2;
        }
    }

    if (len & 1) {  // Need padding
        _rxbuff[_write_index + 1] = spi3.write('\n');
        _rxbuff[_write_index]     = spi3.write(pdata[len - 1]);
        _write_index += 2;
    }

    return len;
}

/**
 * @brief  Delay
 * @param  Delay in ms
 * @retval None
 */
void SPI_WIFI_Delay(uint32_t Delay)
{
    delay(Delay);
}

/**
 * @brief  Delay
 * @param  Delay in us
 * @retval None
 */
void SPI_WIFI_DelayUs(uint32_t n)
{
    volatile uint32_t ct           = 0;
    uint32_t loop_per_us           = 0;
    static uint32_t cycle_per_loop = 0;

    /* calibration happen on first call for a duration of 1 ms * nbcycle per loop */
    /* 10 cycle for STM32L4 */
    if (cycle_per_loop == 0) {
        uint32_t cycle_per_ms = (SystemCoreClock / 1000UL);
        uint32_t t            = 0;
        ct                    = cycle_per_ms;
        t                     = HAL_GetTick();
        while (ct) ct--;
        cycle_per_loop = HAL_GetTick() - t;
        if (cycle_per_loop == 0) cycle_per_loop = 1;
    }

    loop_per_us = SystemCoreClock / 1000000UL / cycle_per_loop;
    ct          = n * loop_per_us;
    while (ct) ct--;
    return;
}
