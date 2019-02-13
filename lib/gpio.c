#include "gpio.h"

static GPIO_TypeDef *GpioGetPointer(uint16_t portNum)
{
    switch (portNum)
    {
    case GPIO_PORT_A:
        if (__HAL_RCC_GPIOA_IS_CLK_DISABLED())
            __HAL_RCC_GPIOA_CLK_ENABLE();
        return GPIOA;
    case GPIO_PORT_B:
        if (__HAL_RCC_GPIOB_IS_CLK_DISABLED())
            __HAL_RCC_GPIOB_CLK_ENABLE();
        return GPIOB;
    case GPIO_PORT_C:
        if (__HAL_RCC_GPIOC_IS_CLK_DISABLED())
            __HAL_RCC_GPIOC_CLK_ENABLE();
        return GPIOC;
    case GPIO_PORT_D:
        if (__HAL_RCC_GPIOD_IS_CLK_DISABLED())
            __HAL_RCC_GPIOD_CLK_ENABLE();
        return GPIOD;
    case GPIO_PORT_E:
        if (__HAL_RCC_GPIOE_IS_CLK_DISABLED())
            __HAL_RCC_GPIOE_CLK_ENABLE();
        return GPIOE;
    }

    return NULL;
}


void GpioInit(uint16_t port, uint32_t pins, uint32_t mode, uint16_t speed, uint32_t pull)
{
    GPIO_InitTypeDef cfg;
    cfg.Pin = pins;
    cfg.Mode = mode;
    cfg.Pull = pull;
    cfg.Speed = speed;

    HAL_GPIO_Init(GpioGetPointer(port), &cfg);
}

void GpioOn(uint16_t port, uint32_t pins)
{
    HAL_GPIO_WritePin(GpioGetPointer(port), pins, GPIO_PIN_SET);
}

void GpioOff(uint16_t port, uint32_t pins)
{
    HAL_GPIO_WritePin(GpioGetPointer(port), pins, GPIO_PIN_RESET);
}

bool GpioState(uint16_t port, uint32_t pin)
{
    return HAL_GPIO_ReadPin(GpioGetPointer(port), pin);
}