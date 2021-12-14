#include <stdio.h>
#include "pico/stdlib.h"

#include "serialUtils.h"

uint32_t GetOption(void) {
    uint32_t acum = 0;
    int character;

    character = getchar_timeout_us(0);
    if (character != PICO_ERROR_TIMEOUT && character != ENTER){
        do
        {
            if (character >= '0' && character <= '9'){
                acum = acum*10 + (character & 0x0F);
            }
        }
        while((character = getchar()) != ENTER);
        
        if (acum < 1 || acum > 2){
            printf("Opcion incorrecta. Recuerde ingresar 1 o 2.\n\n", acum);
            acum = PICO_ERROR_TIMEOUT; 
            printf(MENU_MESSAGE);
        }else{
            printf("Opcion correcta.\n\n");
        }
        
    }else{
        acum = PICO_ERROR_TIMEOUT;
    }

    return (acum);
}

uint32_t GetThreshold(uint8_t minThreshold, uint8_t maxThreshold) {
    uint32_t acum = 0;
    int character;
    bool charPresence = false;

    printf("\nIngrese un valor entre %d y %d: ", minThreshold, maxThreshold);
    character = getchar_timeout_us(0);

    if (character != PICO_ERROR_TIMEOUT){
        do
        {
            if (character >= '0' && character <= '9'){
                acum = acum*10 + (character & 0x0F);
            }else{
                charPresence = true;
            }
        }
        while((character = getchar()) != ENTER);

        if (charPresence || acum < minThreshold){
            printf("El valor ingresado es menor al valor minimo aceptado (%d).\n\n", minThreshold);
        }else if (acum > maxThreshold){
            printf("El valor ingresado es mayor al valor maximo aceptado (%d).\n\n", maxThreshold);
        }else{
            printf("Valor de umbral actualizado correctamente a: %d.\n\n", acum);
        }
        printf(MENU_MESSAGE);
        
    }else{
        acum = PICO_ERROR_TIMEOUT;
    }

    return (acum);
}
