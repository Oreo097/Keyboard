#ifndef __SERIAL_LOG_H
#define __SERIAL_LOG_H

#ifndef _STDIO_H_
#include <stdio.h>
#endif

#include "main.h"

// #ifndef __STM32F1xx_HAL_CONF_H
// #include "stm32f1xx_hal_conf.h"
// #endif

// #ifndef __usart_H
// #include "usart.h"
// #endif

// #ifndef __dma_H
// #include "dma.h"
// #endif

// #ifndef __STM32F1xx_IT_H
// #include "stm32f1xx_it.h"
// #endif

// #ifndef __STM32F1xx_H
// #include "stm32f1xx.h"
// #endif



/**
 * 输出串口的函数——通过重写printf的底层函数来实现printf输出串口的功能
 * 使用本函数需要打开DMA中断
 * 移植本函数时需要注意宏定义
*/


#define PROTOTYPE int fputc(int ch,FILE *f)

#define huart_debug huart1

// #define print_info print("FILE:%S\t\tLINE:%d%s",__FILE__,__LINE__,__VA_ARGS__)


void print(uint8_t * string);

extern UART_HandleTypeDef huart1;

#endif