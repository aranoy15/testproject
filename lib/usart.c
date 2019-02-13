#include "usart.h"
#include "gpio.h"
#include "string.h"

static void UsartInitGpio(uint8_t port);
static USART_TypeDef *UsartGetPointer(uint8_t port);
static void UsartPutBuf(UART_HandleTypeDef *huart, const uint8_t *buf);

void UsartInit(UART_HandleTypeDef *huart, uint8_t port, uint32_t baudrate)
{
    huart->Instance = UsartGetPointer(port);
    huart->Init.BaudRate = baudrate;
    huart->Init.WordLength = UART_WORDLENGTH_8B;
    huart->Init.StopBits = UART_STOPBITS_1;
    huart->Init.Parity = UART_PARITY_NONE;
    huart->Init.Mode = UART_MODE_TX_RX;
    huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart->Init.OverSampling = UART_OVERSAMPLING_16;

    UsartInitGpio(port);
    HAL_UART_Init(huart);
}

void UsartPutsFormat(UART_HandleTypeDef *huart, const char *fmt, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    UsartPutBuf(huart, (const uint8_t*)buffer);
    UsartPutBuf(huart, (const uint8_t*)"\r\n");
}

void UsartPuts(UART_HandleTypeDef *huart, const char *message)
{
    UsartPutBuf(huart, (const uint8_t*)message);
    UsartPutBuf(huart, (const uint8_t*)"\r\n");
}

USART_TypeDef *UsartGetPointer(uint8_t port)
{
    switch (port) {
        case USART_PORT_1:
            return USART1;
    }

    return NULL;
}

void UsartInitGpio(uint8_t port)
{
    switch (port) {
        case USART_PORT_1:
            if (__HAL_RCC_USART1_IS_CLK_DISABLED()) __HAL_RCC_USART1_CLK_ENABLE();

            GpioInit(GPIO_PORT_A, GPIO_PIN_9 | GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_SPEED_FREQ_HIGH, GPIO_NOPULL);
            break;
    }
}

void UsartPutBuf(UART_HandleTypeDef *huart, const uint8_t *buf)
{
    HAL_UART_Transmit(huart, (uint8_t*)buf, strlen((const char*)buf), 1000);
}