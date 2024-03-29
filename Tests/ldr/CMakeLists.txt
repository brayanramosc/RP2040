# Versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.12)

# Incluir funciones de SDK de PICO
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Nombre del proyecto y estándares del lenguaje aceptados
project(LDR C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Inicialización de varios elementos del proyecto
pico_sdk_init()

# Indicarle a CMake los archivos de nuestro programa
add_executable(${PROJECT_NAME}
        LDR.c 
)

# Habilitar comunicación por USB
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Crear archivos de salida
pico_add_extra_outputs(${PROJECT_NAME})

# Enlazar a las librerías requeridas
target_link_libraries(
        ${PROJECT_NAME}
        pico_stdlib
        hardware_adc
)
