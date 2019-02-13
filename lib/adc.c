#include "adc.h"
#include "gpio.h"

static ADC_TypeDef *AdcGetPointer(uint8_t port);
static void AdcInitGpio(uint8_t port);
static void AdcInitChannel(ADC_HandleTypeDef *adchndl, uint32_t channel);


void AdcInit(ADC_HandleTypeDef *adchndl, uint8_t port)
{
    adchndl->Instance = AdcGetPointer(port);
    adchndl->Init.ScanConvMode = ADC_SCAN_DISABLE;
    adchndl->Init.ContinuousConvMode = DISABLE;
    adchndl->Init.DiscontinuousConvMode = DISABLE;
    adchndl->Init.ExternalTrigConv = ADC_SOFTWARE_START;
    adchndl->Init.DataAlign = ADC_DATAALIGN_RIGHT;
    adchndl->Init.NbrOfConversion = 1;

    AdcInitGpio(port);
    HAL_ADC_Init(adchndl);
}

float AdcRead(ADC_HandleTypeDef *adchndl, uint32_t channel)
{
    AdcInitChannel(adchndl, channel);
    HAL_ADC_Start(adchndl);
    HAL_ADC_PollForConversion(adchndl, 100);
    uint32_t result = HAL_ADC_GetValue(adchndl);
    HAL_ADC_Stop(adchndl);
    return (float)(result * 3.3f / 4096.0f);
}

ADC_TypeDef *AdcGetPointer(uint8_t port)
{
    switch (port) {
        case ADC_PORT_1:
            return ADC1;
    }

    return NULL;
}

void AdcInitGpio(uint8_t port)
{
    switch (port) {
        case ADC_PORT_1:
            if (__HAL_RCC_ADC1_IS_CLK_DISABLED()) __HAL_RCC_ADC1_CLK_ENABLE();

            GpioInit(GPIO_PORT_A, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4, GPIO_MODE_ANALOG, GPIO_SPEED_FREQ_HIGH, GPIO_NOPULL);
            break;
    }
}

void AdcInitChannel(ADC_HandleTypeDef *adchndl, uint32_t channel)
{
    ADC_ChannelConfTypeDef config = {0};

    config.Channel = channel;
    config.Rank = ADC_REGULAR_RANK_1;
    config.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;

    HAL_ADC_ConfigChannel(adchndl, &config);
}