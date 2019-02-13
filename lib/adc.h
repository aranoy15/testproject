#ifndef ADC_H
#define ADC_H

#include "stm32f1xx_hal.h"
#include "inttypes.h"

#define ADC_PORT_1 ((uint8_t)1)

void AdcInit(ADC_HandleTypeDef *adchndl, uint8_t port);
float AdcRead(ADC_HandleTypeDef *adchndl, uint32_t channel);

#endif /* ADC_H */