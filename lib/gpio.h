#ifndef GPIO_H
#define GPIO_H

#include "stm32f1xx_hal.h"
#include "inttypes.h"
#include "stdbool.h"

#define GPIO_PORT_A (uint16_t)(0u)
#define GPIO_PORT_B (uint16_t)(1u)
#define GPIO_PORT_C (uint16_t)(2u)
#define GPIO_PORT_D (uint16_t)(3u)
#define GPIO_PORT_E (uint16_t)(4u)

void GpioInit(uint16_t port, uint32_t pins, uint32_t mode, uint16_t speed, uint32_t pull);
void GpioOn(uint16_t port, uint32_t pins);
void GpioOff(uint16_t port, uint32_t pins);
bool GpioState(uint16_t port, uint32_t pin);

#endif /* GPIO_H */