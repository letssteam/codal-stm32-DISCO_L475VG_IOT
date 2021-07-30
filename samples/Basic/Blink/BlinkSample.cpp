#include "BlinkSample.h"

void initializeGpioPinAsOutput(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    __GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin   = GPIO_Pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void BlinkSample_main(codal::STM32DISCO_L475VG_IOT& discoL475VgIot)
{
    initializeGpioPinAsOutput(GPIOA, GPIO_PIN_5);

    while (true) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        discoL475VgIot.sleep(1000);
    }
}
