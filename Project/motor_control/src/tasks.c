#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "tasks.h"
#include "events.h"
#include "pwm.h"
#include "uart_bt.h"

typedef struct {
    uint8_t id;
    uint32_t delay;
    SemaphoreHandle_t *dmutex;
}task_t;

void getBytesTask (void * pvParams) {
    uint8_t ID = ((task_t *)pvParams)->id;
    //uint32_t delay = ((task_t *)pvParams)->delay;
    SemaphoreHandle_t * xMtx = ((task_t *)pvParams)->dmutex;
    uint8_t cnt = 0;

    while (true) {
        if (EV_UART_RX) {
            EV_UART_RX = false;
			read_data_from_uart();

            if (++cnt == 7) {
                cnt = 0;
                if (id == OPEN_LOOP_BYTE) {
                    EV_OPEN_LOOP = true;
                    printf("Data Task \n");
                }
            }
		}
    }  
}

void openLoopTask (void * pvParams) {
    uint8_t ID = ((task_t *)pvParams)->id;
    //uint32_t delay = ((task_t *)pvParams)->delay;
    SemaphoreHandle_t * xMtx = ((task_t *)pvParams)->dmutex;

    while (true) {
        //vTaskDelay(delay);
        if (EV_OPEN_LOOP) {
            EV_OPEN_LOOP = false;
            printf("Open Loop Task \n");

            if(isValidFrame && mode == CONTROL_BYTE ) {
                isValidFrame = false;
                pwm_change_level((uint16_t)((uint32_t)(dataBuffer[2]*PWM_TOP/100)));
            }
        }
    }  
}

void createTasks (void) {
    BaseType_t xReturned;

    void (*ptrArray[2])(void *) = {getBytesTask, openLoopTask};
    TaskHandle_t taskHandleArray[2];
    uint32_t taskDelay[2] = {10, 5000};
    char taskNames[] = "GBTask\nOLTask\n";
    task_t taskArray[2];

    for (int i = 0; i < 2; i++) {
        taskArray[i].id = i;
        taskArray[i].delay = taskDelay[i];
        taskArray[i].dmutex = NULL;

        xReturned = xTaskCreate(ptrArray[i], &taskNames[i*7], 1000, &taskArray[i], 2, &taskHandleArray[i]);
        if (xReturned == pdPASS)
            printf("%s created succesfully\n", &taskNames[i*7]);
    }

    vTaskStartScheduler();
    panic_unsupported();
}
