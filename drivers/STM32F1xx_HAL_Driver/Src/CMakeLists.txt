target_sources(drivers PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_adc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_adc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_cortex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_flash_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_gpio_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_pwr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_rcc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_tim_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f1xx_hal.c
)
