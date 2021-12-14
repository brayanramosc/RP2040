// Libraries
#include <stdio.h>
#include "pico/stdlib.h"

const uint FAN_PIN = 2;

const char MENU_MESSAGE[] = "Sensado y Control\n\n1. Ver valores de las variables.\n2. Cambiar umbrales.\n\nOpcion: ";

int main()
{
    // Initialization
    stdio_init_all();
    gpio_init(FAN_PIN);
    gpio_set_dir(FAN_PIN, GPIO_OUT);
    gpio_put(FAN_PIN, true);

    char option;

    // Check for USB connection
    while (!stdio_usb_connected()) {
        printf(".");
        sleep_ms(500);
    }

    // Infinite loop
    while (true){
        printf("\n");
        printf(MENU_MESSAGE);
        option = getchar();

        switch (option){
            case '1':
                printf( "%c.\n", option);
                gpio_put(FAN_PIN, false);
                //sleep_ms(2000);
                break;
            case '2':
                printf( "%c.\n", option);
                gpio_put(FAN_PIN, true);
                //sleep_ms(2000);
                break;
            default:
                printf( "Opcion incorrecta.\n");
                //sleep_ms(2000);
                break;
        }
    }
    
    return 0;
}
