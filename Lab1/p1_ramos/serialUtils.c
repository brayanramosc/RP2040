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

        switch (acum)
        {
            case 1:
                printf("Opcion correcta.\n\n");
                break;
            case 2:
                printf("Opcion correcta.\n\n");
                break;
            
            default:
                printf("Opcion incorrecta. Recuerde ingresar 1 o 2.\n\n", acum);
                acum = PICO_ERROR_TIMEOUT; 
                printf(MENU_MESSAGE);
                break;
        }
        
    }else{
        acum = PICO_ERROR_TIMEOUT;
    }

    return (acum);
}

uint32_t TestFunction(uint32_t* auxTemp, 
                      uint32_t* auxLightPerc, 
                      float tempRead, 
                      float lightRead,
                      uint8_t minTempThreshold,
                      uint8_t maxTempThreshold,
                      uint8_t minlightThreshold,
                      uint8_t maxlightThreshold) 
{
    uint32_t acum = 0;
    uint32_t tempAcum = 0;
    uint32_t lightAcum = 0;
    int character;
    bool charPresence = false;

    character = getchar_timeout_us(0);
    if (character != PICO_ERROR_TIMEOUT && character != ENTER)
    {
        do
        {
            if (character >= '0' && character <= '9'){
                acum = acum*10 + (character & 0x0F);
            }
        }
        while((character = getchar()) != ENTER);

        switch (acum)
        {

            case 1:
                printf("Opcion correcta.\n\n");
                printf("Valores: \n");
                printf("Temperatura: %.2f grados Celsius\t", tempRead);
                printf("Porcentaje de luz: %.2f%%\n\n", lightRead);
                printf(MENU_MESSAGE);
                break;
            case 2:
                printf("Opcion correcta.\n");
                get_temperature: printf("Actualice el umbral para la temperatura.\n");
                printf("Ingrese un valor entre %d y %d: \n", minTempThreshold, maxTempThreshold);
                
                while ((character = getchar()) != ENTER) {
                    if (character >= '0' && character <= '9') {
                        tempAcum = tempAcum*10 + (character & 0x0F);
                    }
                }

                if (charPresence || tempAcum < minTempThreshold){
                    printf("El valor ingresado es menor al valor minimo aceptado (%d).\n\n", minTempThreshold);
                    tempAcum = 0;
                    goto get_temperature;
                }else if (tempAcum > maxTempThreshold){
                    printf("El valor ingresado es mayor al valor maximo aceptado (%d).\n\n", maxTempThreshold);
                    tempAcum = 0;
                    goto get_temperature;
                }else{
                    printf("Valor de umbral actualizado correctamente a: %d.\n\n", tempAcum);
                    *auxTemp = tempAcum;
                }

                get_light_perc: printf("Actualice el umbral para el porcentaje de luz.\n");
                printf("Ingrese un valor entre %d y %d: \n", minlightThreshold, maxlightThreshold);

                while ((character = getchar()) != ENTER) {
                    if (character >= '0' && character <= '9') {
                        lightAcum = lightAcum*10 + (character & 0x0F);
                    }
                }

                if (charPresence || lightAcum < minlightThreshold){
                    printf("El valor ingresado es menor al valor minimo aceptado (%d).\n\n", minlightThreshold);
                    lightAcum = 0;
                    goto get_light_perc;
                }else if (lightAcum > maxlightThreshold){
                    printf("El valor ingresado es mayor al valor maximo aceptado (%d).\n\n", maxlightThreshold);
                    lightAcum = 0;
                    goto get_light_perc;
                }else{
                    printf("Valor de umbral actualizado correctamente a: %d.\n\n", lightAcum);
                    *auxLightPerc = lightAcum; 
                    printf(MENU_MESSAGE);
                }
                break;
            
            default:
                printf("Opcion incorrecta. Recuerde ingresar 1 o 2.\n\n", acum);
                acum = PICO_ERROR_TIMEOUT; 
                printf(MENU_MESSAGE);
                break;
        }
    }
    else
    {
        acum = PICO_ERROR_TIMEOUT;
    }

    return (acum);
}

uint32_t GetThreshold(uint8_t minThreshold, uint8_t maxThreshold) {
    uint32_t acum = 0;
    int character;
    bool charPresence = false;

    character = getchar_timeout_us(0);

    if (character != PICO_ERROR_TIMEOUT && character != ENTER){
        printf("\nIngrese un valor entre %d y %d: \n", minThreshold, maxThreshold);
        do
        {
            if (character >= '0' && character <= '9'){
                acum = acum*10 + (character & 0x0F);
            }else{
                charPresence = true;
            }
        }
        while((character = getchar()) != ENTER);
        printf("Data: char: %c \t acum: %d \n", character, acum);

        if (charPresence || acum < minThreshold){
            printf("El valor ingresado es menor al valor minimo aceptado (%d).\n\n", minThreshold);
            acum = PICO_ERROR_TIMEOUT;
        }else if (acum > maxThreshold){
            printf("El valor ingresado es mayor al valor maximo aceptado (%d).\n\n", maxThreshold);
            acum = PICO_ERROR_TIMEOUT;
        }else{
            printf("Valor de umbral actualizado correctamente a: %d.\n\n", acum);
        }
        
    }else{
        acum = PICO_ERROR_TIMEOUT;
    }

    return (acum);
}
