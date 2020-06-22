#include "wiring_time.h"

#include "STM32Pin.h"
#include "STM32IotNode.h"

using namespace codal;


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