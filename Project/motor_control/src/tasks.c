#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "tasks.h"

typedef struct {
    uint8_t id;
    uint32_t delay;
    SemaphoreHandle_t *dmutex;
}task_t;

void openLoopTask (void * pvParams) {
    uint8_t ID = ((task_t *)pvParams)->id;
    uint32_t delay = ((task_t *)pvParams)->delay;
    SemaphoreHandle_t * xMtx = ((task_t *)pvParams)->dmutex;

    while (true) {
        printf("Task %s executing on core %d\n", pcTaskGetName(NULL), get_core_num());
        vTaskDelay(delay);
    }  
}

void createTasks (void) {
    printf("Creando tareas! \n\n");
    BaseType_t xReturned;

    TaskHandle_t taskHandleArray[1];
    uint32_t taskDelay = 5000;
    char taskNames[] = "OLTask\n";
    task_t taskArray[1];

    for (int i = 0; i < 1; i++) {
        taskArray[i].id = i;
        taskArray[i].delay = taskDelay;
        taskArray[i].dmutex = NULL;

        xReturned = xTaskCreate(openLoopTask, &taskNames[i*7], 1000, &taskArray[i], 2, &taskHandleArray[i]);
        if (xReturned == pdPASS)
            printf("%s created succesfully\n", &taskNames[i*7]);
    }

    printf("Core %d\n", get_core_num());
    vTaskStartScheduler();

    panic_unsupported();
}
