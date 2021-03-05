#ifndef __KBD_FUNCTIONS_H__
#define __KBD_FUNCTIONS_H__

#include "main.h"
#include "gpio.h"

uint8_t KBD_GPIO_READ();

void KBD_GPIO_WRITE();

void KBD_GPIO_UP();

void KBD_GPIO_DOWN();

void KBD_USART_SEND(uint8_t * message,uint8_t length);

int dbg(char[] message);



//************************变量定义*************************/

//定义GPIO数组
typedef struct
{
    type_gpio *gpio_group;

    uint8_t gpio_pin;

} kbd_gpio_t;

#endif