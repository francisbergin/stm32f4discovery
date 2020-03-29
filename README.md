# stm32f4discovery

This project contains the files and configurations necessary to quickly get running with FreeRTOS on the STM32F4 Discovery board.

Parts of this project are discussed here: https://berfr.me/posts/getting-started-stm32f4-freertos/.

## dependencies

- CMake
- `gcc-arm-none-eabi` toolchain
- [texane/stlink](https://github.com/texane/stlink)
- [STM32F4DISCOVERY kit](https://www.st.com/en/evaluation-tools/stm32f4discovery.html)

## based on

- FreeRTOSv10.2.1
- STM32F4xx\_DSP\_StdPeriph\_Lib\_V1.8.0
    - CMSIS V4.00
- STM32F4-Discovery\_FW\_V1.1.0

## setup

```shell
# setup output directory
mkdir bin && cd bin
cmake ..

# build and run example
make blink_leds.elf
make blink_leds.bin-flash
```

## other

```shell
# sync lib files
rsync -a -v --files-from=lib-files-freertos.txt ../embedded-libs/FreeRTOSv10.2.1/ lib/freertos/
rsync -a -v --files-from=lib-files-stm32f4discovery.txt ../embedded-libs/STM32F4-Discovery_FW_V1.1.0/ lib/stm32f4discovery/
rsync -a -v --files-from=lib-files-stm32f4xx.txt ../embedded-libs/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0/ lib/stm32f4xx/
```

## license

The files under `lib/` are licensed according to their specific licenses.

The rest of the project is licensed under the MIT license.
