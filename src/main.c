#include "stm32f4_discovery.h"

#include "FreeRTOS.h"
#include "task.h"

typedef struct {
    Led_TypeDef led;
    int delay_ms;
} LedTaskParam;

static const LedTaskParam param1 = { .led = LED4, .delay_ms = 200 };
static const LedTaskParam param2 = { .led = LED5, .delay_ms = 800 };

static void led_task(void *args) {
    LedTaskParam param = *(LedTaskParam*) args;
    while (1) {
        STM_EVAL_LEDToggle(param.led);
        vTaskDelay(pdMS_TO_TICKS(param.delay_ms));
    };
}

int main(void) {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5);

    xTaskCreate(led_task, "LED_blink_1", 128, (void*)&param1, configMAX_PRIORITIES-1, NULL);
    xTaskCreate(led_task, "LED_blink_2", 128, (void*)&param2, configMAX_PRIORITIES-1, NULL);

    vTaskStartScheduler();
    while (1) {}
    return 0;
}
