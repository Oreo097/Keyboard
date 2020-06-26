#ifndef __KBD_FUNC_H
#define __KBD_FUNC_H

#ifndef __MAIN_H
#include "main.h"
#endif


#ifndef __KBD_INFO_H
#include "kbd_info.h"
#endif

// #define pinRead(gpio_group,gpio_pin) HAL_GPIO_ReadPin((gpio_group),(gpio_pin))

// #define pinUp(gpio_group,gpio_pin) HAL_GPIO_WritePin((gpio_group),(gpio_pin),1)

// #define pinDown(gpio_group,gpio_pin) HAL_GPIO_WritePin((gpio_group),(gpio_pin),0)


uint8_t pinRead(kbd_gpio_t gpio);

void pinUp(kbd_gpio_t gpio);

void pinDown(kbd_gpio_t gpio);

void KBD_USB_SEND(uint8_t * report);






#endif