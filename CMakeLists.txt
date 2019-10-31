cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
enable_language(ASM)

file(GLOB_RECURSE LIB_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} lib/*.c lib/*.s)

file(GLOB_RECURSE LIB_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} lib/*.h)
list(TRANSFORM LIB_HEADERS REPLACE "/[^/]+\.h$" "" OUTPUT_VARIABLE LIB_HEADERS_DIRS)
list(REMOVE_DUPLICATES LIB_HEADERS_DIRS)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.c)

include_directories(inc ${LIB_HEADERS_DIRS})

set(LINKER_SCRIPT_INPUT lib/stm32f4xx/Project/STM32F4xx_StdPeriph_Templates/TrueSTUDIO/STM32F40_41xxx/STM32F417IG_FLASH.ld)
set(LINKER_SCRIPT_OUTPUT stm32_flash.ld)
configure_file(${LINKER_SCRIPT_INPUT} ${LINKER_SCRIPT_OUTPUT} COPYONLY)

add_definitions(
    -DSTM32F40_41xxx
    -DHSE_VALUE=\(\(uint32_t\)8000000\)
    -DHSI_VALUE=\(\(uint32_t\)16000000\)
    -DUSE_STDPERIPH_DRIVER
)

set(
    CPU_FLAGS
    -mcpu=cortex-m4 -mlittle-endian -mthumb -mthumb-interwork
    -mfloat-abi=hard -mfpu=fpv4-sp-d16
    -g -O0
)

add_compile_options(
    ${CPU_FLAGS}
    -fdata-sections -ffunction-sections
)

add_link_options(
    ${CPU_FLAGS}
    --specs=nosys.specs
    -T${LINKER_SCRIPT_OUTPUT}
    -Wl,--gc-sections
)

add_executable(main.elf ${SOURCES} ${LIB_SOURCES})

add_custom_target(main.bin ALL arm-none-eabi-objcopy -O binary main.elf main.bin DEPENDS main.elf)
add_custom_target(size ALL arm-none-eabi-size -A main.elf DEPENDS main.elf)
add_custom_target(flash ALL st-flash --reset write main.bin 0x8000000 DEPENDS main.bin)