#ifndef _SERIALUTILS_H
#define _SERIALUTILS_H

#define ENTER 13
#define MENU_MESSAGE "Sensado y Control\n\n1. Ver valores de las variables.\n2. Cambiar umbrales.\n\nOpcion: "

uint32_t GetOption(void);
uint32_t GetThreshold(uint8_t, uint8_t);

#endif