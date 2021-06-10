
#include "CodalFiber.h"
#include "STM32DISCO_L475VG_IOT.h"
using namespace codal;

int main()
{
    STM32DISCO_L475VG_IOT discoL475VgIot;
    discoL475VgIot.init();
    while (1) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        discoL475VgIot.sleep(1000);
    }
    release_fiber();
    return 0;
}
