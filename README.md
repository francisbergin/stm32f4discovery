# stm32f4discovery

## dependencies

- CMake
- `gcc-arm-none-eabi` toolchain
- [texane/stlink](https://github.com/texane/stlink)
- [stm32f4discovery](https://www.st.com/en/evaluation-tools/stm32f4discovery.html)

## setup

```shell
# setup output directory
mkdir bin && cd bin
cmake ..

# build and run project
make main.bin
make flash
```

## other

```shell
# sync lib files
rsync -a -v --files-from=lib-files-freertos.txt ../embedded-libs/FreeRTOSv10.2.1/ lib/freertos/
rsync -a -v --files-from=lib-files-stm32f4xx.txt ../embedded-libs/STM32F4xx_DSP_StdPeriph_Lib_V1.8.0/ lib/stm32f4xx/
rsync -a -v --files-from=lib-files-stm32f4discovery.txt ../embedded-libs/STM32F4-Discovery_FW_V1.1.0/ lib/stm32f4discovery/
```
