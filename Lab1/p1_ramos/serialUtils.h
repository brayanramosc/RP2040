#ifndef _SERIALUTILS_H
#define _SERIALUTILS_H

#define ENTER 13
#define MENU_MESSAGE "Sensado y Control\n\n1. Ver valores de las variables.\n2. Cambiar umbrales.\n\nOpcion: "

uint32_t GetMenuOption(uint32_t*, 
                      uint32_t*, 
                      float, 
                      float,
                      uint8_t,
                      uint8_t,
                      uint8_t,
                      uint8_t);

bool GetValue(uint32_t*, uint8_t, uint8_t);

#endif
