#include "wiring_time.h"
#include "board.h"

#include "STM32Pin.h"
#include "STM32IotNode.h"

using namespace codal;

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need HAL may fail.
__attribute__((constructor(101))) void premain()
{
  init();
}

int main()
{
    STM32IotNode iotnode;
    int pin_state = 0;

    while (1) {
        pin_state = !pin_state;
        if (pin_state) {
            iotnode.io.led1.setDigitalValue(HIGH);
            iotnode.io.led2.setDigitalValue(LOW);
        } else {
            iotnode.io.led1.setDigitalValue(LOW);
            iotnode.io.led2.setDigitalValue(HIGH);
        }
        delay(500);
        //iotnode.sleep(500);
    }
}