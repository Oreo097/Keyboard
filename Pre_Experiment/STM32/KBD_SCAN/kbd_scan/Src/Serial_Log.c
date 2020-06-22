#include "Serial_Log.h"


void print(uint8_t * string)
{
    HAL_UART_Transmit_DMA(&huart_debug,string,sizeof(string));
    return;
}

PROTOTYPE
{
    HAL_UART_Transmit(&huart_debug,(uint8_t *)&ch,1,0xffff);
}