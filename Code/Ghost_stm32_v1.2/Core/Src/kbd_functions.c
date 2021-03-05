#include "kbd_functions.h"

//本文件主要用来重写HAL库的底层函数，方便移植


/**************************************GPIO***********************************************/
//这是GPIO部分

//读
uint8_t KBD_GPIO_READ(kbd_gpio_t key)
{
    uint8_t status=0;
    status=HAL_GPIO_ReadPin(key.gpio_group,key.gpio_pin);
    return status;
}
//写
void KBD_GPIO_WRITE(kbd_gpio_t key,GPIO_PinState state)
{
    HAL_GPIO_WritePin(key.gpio_group,key.gpio_pin,state);
}

//二次封装
//拉高
void KBD_GPIO_UP(kbd_gpio_t key)
{
    HAL_GPIO_WritePin(key.gpio_group,key.gpio_pin,GPIO_PIN_SET);
}

//拉低
void KBD_GPIO_DOWN(kbd_gpio_t key)
{
    HAL_GPIO_WritePin(key.gpio_group,key.gpio_pin,GPIO_PIN_RESET);
}

/*****************************************USART****************************************/
//串口部分


//这是使用串口输出的函数


//包装底层函数
void KBD_USART_SEND(uint8_t * message,uint8_t length)
{
    HAL_UART_Transmit(&huart,message,length,100);
}



//重写串口调试函数，上述方法需要重复调用同一个函数，效率低下
uint8_t dbg(char[] message)
{
    KBD_USART_SEND(message[0],sizeof(message));
    return 0;
}

/*************************************TIM*************************************/
//计时器中断部分

