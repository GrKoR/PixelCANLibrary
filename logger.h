#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <string.h>

#ifndef LOG

    #ifdef DEBUG

        #ifdef DEBUG_X64

            #define LOGstring(fmt, ...)                  \
                do                                       \
                {                                        \
                    fprintf(stderr, fmt, ##__VA_ARGS__); \
                } while (0)

        #else // DEBUG_X64

            #include "stm32f1xx_hal.h"
            #define LOGstring(fmt, ...)                                                                   \
                do                                                                                        \
                {                                                                                         \
                    extern UART_HandleTypeDef huart1;                                                     \
                    char str_buff[255];                                                                   \
                    sprintf(str_buff, fmt, ##__VA_ARGS__);                                                \
                    if (HAL_UART_Transmit(&huart1, (uint8_t *)str_buff, strlen(str_buff), 100) != HAL_OK) \
                    {                                                                                     \
                        HAL_UART_AbortTransmit(&huart1);                                                  \
                    }                                                                                     \
                } while (0)

        #endif // DEBUG_X64

        #ifdef DEBUG_DETAILED

            #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
            #define LOGwoN(fmt, ...) LOGstring("[%s: %d] " fmt, __FILENAME__, __LINE__, ##__VA_ARGS__)

        #else // DEBUG_DETAILED

            #define LOGwoN(fmt, ...) LOGstring(fmt, ##__VA_ARGS__)

        #endif // DEBUG_DETAILED

        #define LOG(fmt, ...) LOGwoN(fmt "\n", ##__VA_ARGS__)

    #else // DEBUG

        #define LOGstring(fmt, ...)
        #define LOGwoN(fmt, ...)
        #define LOG(fmt, ...)

    #endif // DEBUG

#endif // LOG

#endif // LOGGER_H