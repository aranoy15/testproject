#include "rcc.h"
#include "gpio.h"
#include "usart.h"
#include "adc.h"
#include "timerhal.h"

#include "stm32f1xx_hal.h"
#include "stdbool.h"

#define ACS758_C ADC_CHANNEL_0
#define BATTERY1 ADC_CHANNEL_1
#define BATTERY2 ADC_CHANNEL_2
#define BATTERY3 ADC_CHANNEL_3
#define BATTERY4 ADC_CHANNEL_4

#define M_VPER_AMP ((int)40)
#define ACS_OFFSET ((int)2500)

UART_HandleTypeDef huart1;
ADC_HandleTypeDef adc1;

struct TimerHal timerForceOff;
struct TimerHal timerPrintInfo;

float GetAcsVoltage(void);
float GetAcsAmperage(void);

int main(void)
{
    HAL_Init();
    RccInit();

    TimerHalInit(&timerForceOff);
    TimerHalInit(&timerPrintInfo);

    GpioInit(GPIO_PORT_B, GPIO_PIN_12, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_HIGH, GPIO_NOPULL);
    UsartInit(&huart1, USART_PORT_1, 115200);
    AdcInit(&adc1, ADC_PORT_1);

    GpioOn(GPIO_PORT_B, GPIO_PIN_12);

    bool isForceOff = false;
    TimerHalStart(&timerPrintInfo, 1000);

    while(true) {
        float battery1 = ((AdcRead(&adc1, BATTERY1) / 1000.0f) * (1000 + 250));
        float battery2 = ((AdcRead(&adc1, BATTERY2) / 1000.0f) * (1000 + 350));
        float battery3 = ((AdcRead(&adc1, BATTERY3) / 1000.0f) * (1000 + 650));
        float battery4 = ((AdcRead(&adc1, BATTERY4) / 1000.0f) * (1000 + 3700));
        float acsAmperage = GetAcsAmperage();

        bool needOff = (battery1 < 3.6f) || (battery2 < 3.6f) || (battery3 < 3.6f) || (battery4 < 3.6f);

        if (acsAmperage > 10.0f && !isForceOff) {
            isForceOff = true;
            TimerHalStart(&timerForceOff, 10000);
            GpioOff(GPIO_PORT_B, GPIO_PIN_12);
            UsartPuts(&huart1, "Force off");
            continue;
        }

        if (isForceOff && TimerHalElapsed(&timerForceOff)) {
            isForceOff = false;
            GpioOn(GPIO_PORT_B, GPIO_PIN_12);
            UsartPuts(&huart1, "On after force off");
        } else if (needOff)
            GpioOff(GPIO_PORT_B, GPIO_PIN_12);
        else
            GpioOn(GPIO_PORT_B, GPIO_PIN_12);

        if (TimerHalElapsed(&timerPrintInfo)) {
            UsartPutsFormat(&huart1, "Battery1 = %.2f", battery1);
            UsartPutsFormat(&huart1, "Battery2 = %.2f", battery2);
            UsartPutsFormat(&huart1, "Battery3 = %.2f", battery3);
            UsartPutsFormat(&huart1, "Battery4 = %.2f", battery4);
            UsartPutsFormat(&huart1, "Acs amperage = %.2f", acsAmperage);
            UsartPutsFormat(&huart1, "Is force off = %s", isForceOff ? "yes" : "no");

            TimerHalUpdate(&timerPrintInfo);
        }
    }
}

float GetAcsVoltage(void)
{
    float rawValue = AdcRead(&adc1, ACS758_C);
    return ((rawValue / 1023.0) / 5000);
}

float GetAcsAmperage(void)
{
    float voltage = GetAcsVoltage();
    return ((voltage - ACS_OFFSET) / (float)M_VPER_AMP);
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}