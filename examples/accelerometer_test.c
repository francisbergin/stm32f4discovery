#include <stdbool.h>
#include <stdio.h>

#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"

#include "accelerometer.h"
#include "console.h"
#include "delay.h"

void accelerometer_task() {
    uint8_t buffer[6];
    int8_t x_offset, y_offset, z_offset;
    int8_t x_offset_new, y_offset_new, z_offset_new;

    while (1) {
        accelerometer_read(buffer);

        bool new_offset = false;

        if (x_offset != buffer[0] || y_offset != buffer[2] || z_offset != buffer[4]) {
            new_offset = true;
        }

        x_offset = buffer[0];
        y_offset = buffer[2];
        z_offset = buffer[4];

        if (new_offset) {
            printf("x_offset: %d, y_offset: %d, z_offset: %d\r\n", x_offset, y_offset, z_offset);
        }

        delay_ms(100);
    }
}

int main(void) {
    RCC_PCLK1Config(RCC_HCLK_Div8);

    console_setup();
    accelerometer_setup();
    accelerometer_task();

    return 0;
}
