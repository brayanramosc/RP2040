# Versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.12)

# Incluir funciones de SDK de PICO
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Nombre del proyecto y estándares del lenguaje aceptados
project(main C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Inicialización de varios elementos del proyecto
pico_sdk_init()

# Indicarle a CMake los archivos de nuestro programa
add_executable(${PROJECT_NAME}
        src/main.c
        src/events.c
        src/timer.c
        src/pwm.c
        src/uart_bt.c
)

# Indicarle a CMake la ubicación de los headers
include_directories(include)

# Habilitar comunicación por USB
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Crear archivos de salida
pico_add_extra_outputs(${PROJECT_NAME})

# Enlazar a las librerías requeridas
target_link_libraries(
        ${PROJECT_NAME}
        pico_stdlib
        hardware_uart
        hardware_pwm
        hardware_gpio
        hardware_irq
)