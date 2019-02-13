file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty.c "")
add_library(drivers ${CMAKE_CURRENT_BINARY_DIR}/empty.c)

add_subdirectory(CMSIS)
add_subdirectory(STM32F1xx_HAL_Driver)