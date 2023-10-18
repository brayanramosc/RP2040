#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "tasks.h"
#include "events.h"
#include "pwm.h"
#include "uart_bt.h"

volatile _events_str _events;

uint8_t setPoint = 0;
uint8_t rpm = 0;

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
                }else if (id == CLOSED_LOOP_BYTE) {
                    EV_CLOSED_LOOP = true;
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
            EV_CLOSED_LOOP = false;
            printf("Open Loop Task \n");

            if(isValidFrame && mode == CONTROL_BYTE ) {
                isValidFrame = false;
                pwm_change_level((uint16_t)((uint32_t)(dataBuffer[2]*PWM_TOP/100)));
            }
        }
    }  
}

void closedLoopTask (void * pvParams) {
    uint8_t ID = ((task_t *)pvParams)->id;
    uint32_t delay = ((task_t *)pvParams)->delay;
    SemaphoreHandle_t * xMtx = ((task_t *)pvParams)->dmutex;
    uint8_t error_k = 0;
    uint8_t error_k1 = 0;
    uint8_t m_k = 0;
    uint8_t aux_m_k = 0;
    uint8_t m_k1 = 0;
    uint8_t q0 = 0;
    uint8_t q1 = 0;

    while (true) {
        if (EV_CLOSED_LOOP) {
            if(isValidFrame && mode == CONTROL_BYTE ) {
                isValidFrame = false;
                setPoint = dataBuffer[2];
            }
            
            error_k = abs(setPoint - rpm);
            m_k = q0*error_k + q1*error_k1 + m_k1;
            aux_m_k = (m_k < 0) ? 0 : m_k;
            aux_m_k = (m_k > 100) ? 100 : m_k;
            pwm_change_level((uint16_t)((uint32_t)(aux_m_k*PWM_TOP/100)));
            error_k1 = error_k;
            m_k1 = m_k;
        }
        vTaskDelay(delay);
    }  
}

void getSpeedTask (void * pvParams) {
    uint8_t ID = ((task_t *)pvParams)->id;
    SemaphoreHandle_t * xMtx = ((task_t *)pvParams)->dmutex;
    float period = 0;
    float freq = 0;

    while (true) {
        if (EV_EDGE) {
            EV_EDGE = false;

			period = ((float)(t2-t1)) / 1000000;
            freq = 1 / period;
            rpm = (uint8_t)((freq * 60) / 20);
		}
    }  
}

void sendDataTask (void * pvParams) {
    uint8_t ID = ((task_t *)pvParams)->id;
    uint32_t delay = ((task_t *)pvParams)->delay;
    SemaphoreHandle_t * xMtx = ((task_t *)pvParams)->dmutex;
    uint8_t cnt = 1;

    while (true) {
        dataBuffer[0] = HEADER_BYTE;
        dataBuffer[2] = rpm;

        /*if (cnt == 1) {
            dataBuffer[1] = (MONITOR_BYTE | CURRENT_VALUE_BYTE);
            dataBuffer[3] = (HEADER_BYTE + dataBuffer[1] + dataBuffer[2]) & 0xFF;
            write_data();
            cnt++;
        } else if (cnt == 2) {
            dataBuffer[1] = (MONITOR_BYTE | CURRENT_VALUE_BYTE);
            dataBuffer[3] = (HEADER_BYTE + dataBuffer[1] + dataBuffer[2]) & 0xFF;
            write_data();

            dataBuffer[1] = (MONITOR_BYTE | ERROR_BYTE);
            dataBuffer[3] = (HEADER_BYTE + dataBuffer[1] + dataBuffer[2]) & 0xFF;
            write_data();
            cnt = 1;
        }*/
        
        vTaskDelay(delay);
    }  
}

void createTasks (void) {
    BaseType_t xReturned;

    void (*ptrArray[5])(void *) = {getBytesTask, openLoopTask, closedLoopTask, getSpeedTask, sendDataTask};
    TaskHandle_t taskHandleArray[5];
    uint32_t taskDelay[5] = {10, 5000, 1000, 10, 1000};
    char taskNames[] = "GBTask\nOLTask\nCLTask\nGSTask\nSDTask";
    task_t taskArray[5];

    for (int i = 0; i < 5; i++) {
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
