# Versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_PATH "C:/RPPicoSDK/sdk/pico/pico-sdk")

# Incluir funciones de SDK de PICO
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(FreeRTOS_Kernel_import.cmake)

# Nombre del proyecto y estándares del lenguaje aceptados
project(main C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Inicialización de varios elementos del proyecto
pico_sdk_init()

if (TARGET tinyusb_device)
        # Indicarle a CMake los archivos de nuestro programa
        add_executable(
                ${PROJECT_NAME}
                src/main.c
                src/tasks.c
                src/timer.c
                src/pwm.c
                src/uart_bt.c
        )
        target_include_directories(${PROJECT_NAME} PUBLIC ./)

        # Indicarle a CMake la ubicación de los headers
        include_directories(include)

	pico_set_program_name(${PROJECT_NAME} "main")
	pico_set_program_version(${PROJECT_NAME} "0.1")

        # Enlazar a las librerías requeridas
        target_link_libraries(
                ${PROJECT_NAME}
                FreeRTOS-Kernel
		FreeRTOS-Kernel-Heap1
                pico_stdlib
		pico_multicore
                hardware_uart
                hardware_pwm
                hardware_gpio
                hardware_irq
        )

        # Habilitar comunicación por USB
        pico_enable_stdio_usb(${PROJECT_NAME} 1)
        pico_enable_stdio_uart(${PROJECT_NAME} 0)
        
        # Crear archivos de salida
        pico_add_extra_outputs(${PROJECT_NAME})

elseif(PICO_ON_DEVICE)
        message(WARNING "not building project because TinyUSB submodule is not initialized in the SDK")
endif()
