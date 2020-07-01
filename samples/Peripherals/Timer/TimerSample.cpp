#include "TimerSample.h"
#include "STM32Pin.h"
#include "wiring_time.h"

using namespace codal;

STM32Pin led1(ID_PIN_P19, PinNumber::LED_1, PIN_CAPABILITY_AD);

int state = 0;

void Update_IT_callback(void) {
    led1.setDigitalValue(state);
    state = !state;
}

#if defined(TIM6)
TIM_TypeDef* Instance = TIM5;
#else
TIM_TypeDef* Instance = TIM2;
#endif

HardwareTimer* tim;

void TimerSample_main() {
    // Instantiate HardwareTimer object. Thanks to 'new' instanciation, HardwareTimer is not destructed when this
    // function is finished.
    tim = new HardwareTimer(Instance);
    tim->setOverflow(1, HERTZ_FORMAT);  // 1 Hz
    tim->attachInterrupt(Update_IT_callback);
    tim->setInterruptPriority(12, 3);
    tim->resume();
    while (1) {
    }
}