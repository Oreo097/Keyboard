/*
 * @Descripttion: 本文件中的函数时对STM32 HAL库中的函数进行二次包装，方便移植和其他程序引用
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-09 11:41:53
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-10 23:30:20
 */ 


#ifndef __KBD_FUNC_H
#define __KBD_FUNC_H

#include <stdbool.h>
#include "main.h"
#include "kbd_param.h"

/**
 * @name: Oreo097
 * @msg: 二次封装一些HAL库中的数据类型
 * @param {type} 
 * @return: 
 */

#define KBD_DELAY(time) HAL_Delay((time))

bool pinRead(kbd_gpio_t gpio);

void pinUp(kbd_gpio_t gpio);

void pinDown(kbd_gpio_t gpio);

void KBD_USB_SEND(uint8_t * report);

void* memset(void* s, int c, size_t n);




















#endif
