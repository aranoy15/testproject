#ifndef USART_H
#define USART_H

#include "inttypes.h"
#include "stm32f1xx_hal.h"
#include "stdarg.h"

#define USART_PORT_1 ((uint8_t)1)

void UsartInit(UART_HandleTypeDef *huart, uint8_t port, uint32_t baudrate);
void UsartPutsFormat(UART_HandleTypeDef *huart, const char *fmt, ...);
void UsartPuts(UART_HandleTypeDef *huart, const char *message);

#endif /* USART_H */