/*
 * @Descripttion: 
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-08-04 10:19:02
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-08-04 10:31:16
 */
#ifndef __KBD_FUNC_H
#define __KBD_FUNC_H

#include "kbd_scan.h"

/**
 * @name: Oreo097
 * @msg: 
 * @param {type} 
 * @return {type} 
 */
#define KBD_DELAY(time) HAL_DELAY((time))

bool pinRead(kbd_gpio_t gpio);

void pinUp(kbd_gpio_t gpio);

void pinDown(kbd_gpio_t gpio);

void KBD_USB_SEND(uint8_t * report);

void* memset(void* s, int c, size_t n);

#endif