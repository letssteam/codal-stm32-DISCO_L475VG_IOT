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

#if defined(TIM5)
TIM_TypeDef* Instance = TIM5;
#else
TIM_TypeDef* Instance = TIM2;
#endif

HardwareTimer* MyTim;

extern "C" void yield2(void) {
    for (int i = 0; i < 1234567; i++) {
        {
            asm("nop");
        }
    }
}

void TimerSample_main() {
    // Instantiate HardwareTimer object. Thanks to 'new' instanciation, HardwareTimer is not destructed when this
    // function is finished.
    MyTim = new HardwareTimer(Instance);
    MyTim->setOverflow(10, HERTZ_FORMAT);  // 1 Hz
    MyTim->attachInterrupt(Update_IT_callback);
    MyTim->resume();
    while (1) {
        yield2();
    }
}