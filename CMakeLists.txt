cmake_minimum_required(VERSION 3.5)

set(TARGET main)
set(FLOAT 1)

enable_language(ASM)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

SET(CMAKE_C_FLAGS "-mthumb -g -fno-builtin -mcpu=cortex-m3 -Wall -std=gnu99 -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize" CACHE INTERNAL "c compiler flags")
SET(CMAKE_CXX_FLAGS "-mthumb -g -Weffc++ -fno-exceptions -fno-builtin -mcpu=cortex-m3 -Wall -std=c++11 -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize" CACHE INTERNAL "cxx compiler flags")
SET(CMAKE_ASM_FLAGS "-mthumb -g -mcpu=cortex-m3 -x assembler-with-cpp")

SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections -mthumb -mcpu=cortex-m3 -mabi=aapcs -specs=nosys.specs -T ${CMAKE_CURRENT_SOURCE_DIR}/ports/stm32f103/link.ld")
SET(CMAKE_MODULE_LINKER_FLAGS "-mthumb -mcpu=cortex-m3 -mabi=aapcs")
SET(CMAKE_SHARED_LINKER_FLAGS "-mthumb -mcpu=cortex-m3 -mabi=aapcs")

if (FLOAT)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -u _printf_float")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -u _printf_float")
    set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -u _printf_float")
endif()


add_definitions(-DUSE_HAL_DRIVER)
add_definitions(-DSTM32F103xB)

add_executable(${TARGET} 
    main.c
    system_stm32f1xx.c
)

add_subdirectory(ports)
add_subdirectory(drivers)
add_subdirectory(lib)

target_link_libraries(${TARGET} drivers lib c_nano)

add_custom_target(${TARGET}.size ALL
    arm-none-eabi-size ${CMAKE_BINARY_DIR}/${TARGET}
    DEPENDS ${TARGET}
)

add_custom_target(${TARGET}.bin ALL
		arm-none-eabi-objcopy -Obinary ${CMAKE_BINARY_DIR}/${TARGET} ${CMAKE_BINARY_DIR}/${TARGET}.bin
		DEPENDS ${TARGET}
    )	

add_custom_target(${TARGET}.hex ALL
    arm-none-eabi-objcopy -Oihex ${CMAKE_BINARY_DIR}/${TARGET} ${CMAKE_BINARY_DIR}/${TARGET}.hex
    DEPENDS ${TARGET}
)

add_custom_target(flash
    st-flash write ${CMAKE_BINARY_DIR}/${TARGET}.bin 0x8000000
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    USES_TERMINAL
)

add_custom_target(openocd
    openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/share/openocd/scripts/target/stm32f1x.cfg
    	USES_TERMINAL
)