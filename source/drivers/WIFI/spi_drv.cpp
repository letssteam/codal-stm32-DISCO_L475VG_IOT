#include "spi_drv.h"

#include <stdbool.h>
#include <string.h>

#include <cstdio>

#include "STM32DISCO_L475VG_IOT_IO.h"
#include "Timer.h"
#include "codal_target_hal.h"

/**
 * @brief  Constructor.
 * @param  SPIx   : SPI interface
 * @param  csPin     : chip select pin
 * @param  commandDataReadyPin : SPI IRQ pin
 * @param  resetPin  : reset pin
 * @param  wakeUpPin : wakeup pin
 */
SpiDrvClass::SpiDrvClass(codal::STM32SPI* SPIx, codal::STM32Pin* csPin, codal::STM32Pin* commandDataReadyPin,
                         codal::STM32Pin* resetPin, codal::STM32Pin* wakeUpPin)
    : DriverClass(resetPin, wakeUpPin), ISM43362(SPIx), csPin(csPin), commandDataReadyPin(commandDataReadyPin)
{
}

/**
 * @brief  Select the device.
 * @param  None
 * @retval None
 */
void SpiDrvClass::Spi_Slave_Select()
{
    do {
        csPin->setDigitalValue(0);
    } while (0);
    target_wait(10);
}

/**
 * @brief  Unselect the device.
 * @param  None
 * @retval None
 */
void SpiDrvClass::Spi_Slave_Deselect()
{
    do {
        csPin->setDigitalValue(1);
    } while (0);
    target_wait(10);
}

/**
 * @brief  Get data ready state.
 * @param  None
 * @retval data_ready pin state. This is the spiIRQ pin.
 */
uint8_t SpiDrvClass::Spi_Get_Data_Ready_State()
{
    return commandDataReadyPin->getDigitalValue();
}

/**
 * @brief  Reset the WiFi device.
 * @param  None
 * @retval None
 */
void SpiDrvClass::Spi_Wifi_Reset()
{
    do {
        resetPin->setDigitalValue(0);
        target_wait(10);
        resetPin->setDigitalValue(1);
        target_wait(500);
    } while (0);
}

/**
 * @brief  Initialize the SPI
 * @param  None
 * @retval : 0 if init success, -1 otherwise.
 */
int8_t SpiDrvClass::IO_Init(void)
{
    uint8_t Prompt[6];             // data receive
    uint32_t start;                // start time for timeout
    uint16_t dummy_send = 0x0A0A;  // data to feed the clock
    uint16_t read_value;           // data read

    /* pin configuration                                                       */
    wakeUpPin->setDigitalValue(0);
    csPin->setDigitalValue(1);

    /* Clock = 10MHz (Inventek Wi-Fi module supports up to 20MHz)               */
    ISM43362->setFrequency(10000000);
    ISM43362->setMode(0);
    ISM43362->setBitsOrder(true);

    ISM43362->beginTransaction();

    Spi_Wifi_Reset();

    Spi_Slave_Select();

    start = codal::system_timer_current_time();

    for (uint8_t count = 0; count < 6; count += 2) {
        read_value        = ISM43362->write16(dummy_send);
        Prompt[count]     = (uint8_t)(read_value & 0x00FF);
        Prompt[count + 1] = (uint8_t)((read_value & 0xFF00) >> 8);
    }

    while (Spi_Get_Data_Ready_State()) {
        if ((codal::system_timer_current_time() - start) > 100) {
            Spi_Slave_Deselect();
            printf("timeout io_init\n\r");
            return -1;
        }
    }

    Spi_Slave_Deselect();

    // Check receive sequence
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
void SpiDrvClass::IO_DeInit(void)
{
    ISM43362->endTransaction();
}

/**
 * @brief  delay
 * @param  time in ms
 * @retval None
 */
void SpiDrvClass::IO_Delay(uint32_t time)
{
    target_wait(time);
}

/**
 * @brief  Send Wi-Fi Data through SPI
 * @param  pdata   : pointer to data
 * @param  len     : Data length in byte
 * @param  timeout : send timeout in ms
 * @retval Length of sent data, -1 if send fail
 */
int16_t SpiDrvClass::IO_Send(uint8_t* pdata, uint16_t len, uint32_t timeout)
{
    uint8_t Padding[2];  // padding data
    uint32_t start;      // start time for timeout
    int data_tx = 0;     // data really send
    uint16_t data_send;  // data to send

    start = codal::system_timer_current_time();

    // Wait device ready to receive data
    while (!Spi_Get_Data_Ready_State()) {
        if ((codal::system_timer_current_time() - start) > timeout) {
            Spi_Slave_Deselect();
            return -1;
        }
    }

    // Send data
    Spi_Slave_Select();
    for (data_tx = 0; data_tx < len; data_tx += 2) {
        if (data_tx == len - 1) {
            // Data to send are odd, need padding
            Padding[0] = pdata[len - 1];
            Padding[1] = '\n';
            data_send  = Padding[0] | (Padding[1] << 8);
            ISM43362->write16(data_send);
        }
        else {
            data_send = pdata[data_tx] | (pdata[data_tx + 1] << 8);
            ISM43362->write16(data_send);
        }
    }
    return data_tx;
}

/**
 * @brief  Receive Wi-Fi Data from SPI
 * @param  pdata   : pointer to data
 * @param  len     : Data length in byte
 * @param  timeout : send timeout in mS
 * @retval Length of received data (payload)
 */
int16_t SpiDrvClass::IO_Receive(uint8_t* pData, uint16_t len, uint32_t timeout)
{
    int16_t length = 0;            // length of data receive
    uint8_t tmp[2];                // 2 bytes buffer of receive
    uint32_t start;                // start time for timeout
    uint16_t dummy_send = 0x0A0A;  // data to feed the clock
    uint16_t read_value;           // data read

    start = codal::system_timer_current_time();

    Spi_Slave_Deselect();

    // Wait device reports that it has data to send
    while (!Spi_Get_Data_Ready_State()) {
        if ((codal::system_timer_current_time() - start) >= timeout) {
            return 0;
        }
    }

    // Receive device data
    Spi_Slave_Select();
    start = codal::system_timer_current_time();
    while (Spi_Get_Data_Ready_State()) {
        if ((length < len) || (!len)) {
            read_value = ISM43362->write16(dummy_send);
            tmp[0]     = (uint8_t)(read_value & 0x00FF);
            tmp[1]     = (uint8_t)((read_value & 0xFF00) >> 8);

            /* let some time to hardware to change data ready signal (the IRQpin) */
            if (tmp[1] == 0x15) {
                IO_Delay(1);
            }
            /*This the last data */
            if (!Spi_Get_Data_Ready_State()) {
                if (tmp[1] == 0x15) {
                    // Only 1 byte of data, the other one is padding
                    if ((tmp[0] != 0x15)) {
                        pData[0] = tmp[0];
                        length++;
                    }
                    break;
                }
            }

            pData[0] = tmp[0];
            pData[1] = tmp[1];
            length += 2;
            pData += 2;

            if ((codal::system_timer_current_time() - start) >= timeout) {
                Spi_Slave_Deselect();
                return 0;
            }
        }
        else {
            break;
        }
    }

    Spi_Slave_Deselect();
    return length;
}