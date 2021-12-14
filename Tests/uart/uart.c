/*
    * Hecho por: Brayan Ramos
    * Universidad de Antioquia
    * Dic, 2021 
*/

// Libraries
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/uart.h"

// Definitions
#define UART_ID uart0
#define BAUD_RATE 9600
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE
#define UART_TX_PIN 0
#define UART_RX_PIN 1

const uint FAN_PIN = 25;

const char MENU_MESSAGE[] = "Sensado y Control\n\n1. Ver valores de las variables.\n2. Cambiar umbrales.\n\nOpción: \n";

// Main function
int main(){
    // Initialise UART and Fan pin as output
    uart_init(UART_ID, BAUD_RATE);
    gpio_init(FAN_PIN);
    gpio_set_dir(FAN_PIN, GPIO_OUT);

    // Set GPIO pin for TX and RX
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    uart_puts(UART_ID, MENU_MESSAGE);
    uint8_t option = uart_getc(UART_ID);
    
    if (option == 1){
        uart_puts(UART_ID, "\nSe eligió la opción 1.\n");
        gpio_put(FAN_PIN, true);
    }else if(option == 2){
        uart_puts(UART_ID, "\nSe eligió la opción 2.\n");
        gpio_put(FAN_PIN, false);
    }else{
        uart_puts(UART_ID, "\nSe eligió una opción inválida.\n");
    }
    

    return 0;
}

