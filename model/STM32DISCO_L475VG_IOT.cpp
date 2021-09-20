#include "STM32DISCO_L475VG_IOT.h"

using codal::STM32DISCO_L475VG_IOT;

void STM32DISCO_L475VG_IOT_dmesg_flush();

STM32DISCO_L475VG_IOT* codal::default_device_instance = nullptr;

/**
 * Constructor.
 *
 * Create a representation of a device, which includes member variables
 * that represent various device drivers used to control aspects of the STM32 IOT node.
 */
STM32DISCO_L475VG_IOT::STM32DISCO_L475VG_IOT()
    : lowLevelTimer(TIM5, TIM5_IRQn),
      timer(lowLevelTimer),
      serial(io.rx, io.tx),
      i2c1(&io.sda, &io.scl),
      i2c2(&io.sda2, &io.scl2),
      spi1(io.miso, io.mosi, io.sclk),
      spi3(io.miso3, io.mosi3, io.sclk3)
{
    // Clear our status
    status                  = 0;
    default_device_instance = this;
    default_serial_debug    = &serial;
}

/**
 * Post constructor initialisation method.
 *
 * This call will initialised the scheduler, memory allocator and Bluetooth stack.
 *
 * This is required as the Bluetooth stack can't be brought up in a
 * static context i.e. in a constructor.
 *
 * @code
 * STM32DISCO_L475VG_IOT.init();
 * @endcode
 *
 * @note This method must be called before user code utilises any functionality
 *       contained within the STM32DISCO_L475VG_IOT class.
 */
auto STM32DISCO_L475VG_IOT::init() -> int
{
    if ((status & DEVICE_INITIALIZED) != 0) {
        return DEVICE_NOT_SUPPORTED;
    }

    status |= DEVICE_INITIALIZED;

    // codal_dmesg_set_flush_fn(STM32DISCO_L475VG_IOT_dmesg_flush);

    // Bring up fiber scheduler.
    scheduler_init(messageBus);

    for (auto& component : CodalComponent::components) {
        if (component != nullptr && component != this) {
            component->init();
        }
    }

    status |= DEVICE_COMPONENT_STATUS_IDLE_TICK;

    return DEVICE_OK;
}

WEAK auto __io_putchar(int ch) -> int;

void STM32DISCO_L475VG_IOT_dmesg_flush()
{
#if CONFIG_ENABLED(DMESG_SERIAL_DEBUG)
#if DEVICE_DMESG_BUFFER_SIZE > 0
    if (codalLogStore.ptr > 0 && default_device_instance != nullptr) {
        for (uint32_t i = 0; i < codalLogStore.ptr; i++) {
            __io_putchar(codalLogStore.buffer[i]);
        }
        codalLogStore.ptr = 0;
    }
#endif
#endif
}
