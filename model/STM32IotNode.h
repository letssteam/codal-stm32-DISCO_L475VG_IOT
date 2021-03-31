#ifndef STM32_IOT_NODE_H
#define STM32_IOT_NODE_H

#include "Button.h"
#include "CodalComponent.h"
#include "CodalDevice.h"
#include "CodalDmesg.h"
#include "CodalFiber.h"
#include "DumbSensor.h"
#include "HTS221_Humidity.h"
#include "HTS221_Temperature.h"
#include "LIS3MDL_Magnetometer.h"
#include "LPS22HB_Pressure.h"
#include "LSM6DSL_Accelerometer.h"
#include "LSM6DSL_Gyroscope.h"
#include "MessageBus.h"
#include "NotifyEvents.h"
#include "STM32I2C.h"
#include "STM32IotNodeIO.h"
#include "STM32LowLevelTimer.h"
#include "STM32SPI.h"
#include "STM32Serial.h"
#include "VL53L0X_Distance.h"
#include "codal-core/inc/driver-models/Timer.h"
#include "codal-core/inc/types/Event.h"
#include "stm32_def.h"

// Status flag values
#define DEVICE_INITIALIZED 0x01

/**
 * Class definition for a STM32 IOT node.
 *
 * Represents the device as a whole, and includes member variables that represent various device drivers
 * used to control aspects of the STM32 IOT node.
 */
namespace codal {
class STM32IotNode : public CodalComponent {
  public:
    STM32LowLevelTimer lowLevelTimer;
    Timer timer;
    MessageBus messageBus;

    STM32IotNodeIO io;
    STM32I2C i2c1;  // External on arduino stardard pins
    STM32I2C i2c2;  // Internal only used by MEMS sensors
    STM32Serial serial;
    STM32SPI spi1;
    STM32SPI spi3;

    DumbSensor dumbSensor;
    HTS221_Humidity hygrometer;
    HTS221_Temperature thermometer;
    LPS22HB_Pressure barometer;
    VL53L0X_Distance distance;

    CoordinateSpace coordinateSpace;
    LIS3MDL_Magnetometer magnetometer;
    LSM6DSL_Accelerometer accelerometer;
    LSM6DSL_Gyroscope gyroscope;

    Button buttonUSER;

    /**
     * Constructor.
     */
    STM32IotNode();

    /**
     * Post constructor initialisation method.
     */
    virtual int init() override final;

    /**
     * Delay execution for the given amount of time.
     *
     * If the scheduler is running, this will deschedule the current fiber and perform
     * a power efficient, concurrent sleep operation.
     *
     * If the scheduler is disabled or we're running in an interrupt context, this
     * will revert to a busy wait.
     *
     * Alternatively: wait, wait_ms, wait_us can be used which will perform a blocking sleep
     * operation.
     *
     * @param milliseconds the amount of time, in ms, to wait for. This number cannot be negative.
     *
     */
    static void sleep(uint32_t milliseconds);

    /**
     * A periodic callback invoked by the fiber scheduler idle thread.
     * We use this for any low priority, background housekeeping.
     */
    virtual void idleCallback() override final;

    /**
     * Determine the time since this board was last reset.
     *
     * @return The time since the last reset, in milliseconds.
     *
     * @note This will value overflow after 1.6 months.
     */
    static CODAL_TIMESTAMP systemTime();
};

extern STM32IotNode* default_device_instance;
}  // namespace codal
#endif
