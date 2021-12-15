#include <stdio.h>
#include "pico/stdlib.h"

#include "serialUtils.h"

// Function to get and execute a menu option
uint32_t GetMenuOption(uint32_t* auxTemp, 
                      uint32_t* auxLightPerc, 
                      float tempRead, 
                      float lightRead,
                      uint8_t minTempThreshold,
                      uint8_t maxTempThreshold,
                      uint8_t minlightThreshold,
                      uint8_t maxlightThreshold) 
{
    uint32_t acum = 0;
    int character;

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

                if (!GetValue(auxTemp, minTempThreshold, maxTempThreshold))
                {
                    goto get_temperature;
                }

                get_light_perc: printf("Actualice el umbral para el porcentaje de luz.\n");
                printf("Ingrese un valor entre %d y %d: \n", minlightThreshold, maxlightThreshold);

                if (!GetValue(auxLightPerc, minlightThreshold, maxlightThreshold))
                {
                    goto get_light_perc;
                }
                else
                {
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


// Function to get value (threshold) from terminal
bool GetValue(uint32_t* aux, uint8_t minThreshold, uint8_t maxThreshold){
    int character;
    uint32_t acum = 0;
    bool charPresence = false;

    while ((character = getchar()) != ENTER) 
    {
        if (character >= '0' && character <= '9') 
        {
            acum = acum*10 + (character & 0x0F);
        }
        else
        {
            charPresence = true;
        }
    }

    if (charPresence)
    {
        printf("El valor ingresado contiene caracteres, verifique.\n\n");
        return false;
    }
    else if (acum < minThreshold)
    {
        printf("El valor ingresado es menor al valor minimo aceptado (%d).\n\n", minThreshold);
        return false;
    }
    else if (acum > maxThreshold)
    {
        printf("El valor ingresado es mayor al valor maximo aceptado (%d).\n\n", maxThreshold);
        return false;
    }
    else
    {
        printf("Valor de umbral actualizado correctamente a: %d.\n\n", acum);
        *aux = acum;
    }

    return true;
}
