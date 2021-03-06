/*
 * @Descripttion: 对基础函数进行二次封装
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-01 22:07:59
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-07 23:32:39
 */ 

#ifndef __KBD_FUNC_H
#define __KBD_FUNC_H

#ifndef __KBD_CONFIG_H
#include "kbd_config.h"
#endif





#ifndef __MAIN_H
#include "main.h"
#endif


#ifndef __KBD_INFO_H
#include "kbd_info.h"
#endif

#ifndef __USB_DEVICE_H
#include "usb_device.h"
#endif


// #define pinRead(gpio_group,gpio_pin) HAL_GPIO_ReadPin((gpio_group),(gpio_pin))

// #define pinUp(gpio_group,gpio_pin) HAL_GPIO_WritePin((gpio_group),(gpio_pin),1)

// #define pinDown(gpio_group,gpio_pin) HAL_GPIO_WritePin((gpio_group),(gpio_pin),0)



/**
 * @name: Oreo097
 * @msg: 使用宏定义来写HAL库中的延迟函数
 * @param {type} 
 * @return: 
 */
#define KBD_DELAY(time) HAL_Delay((time))

uint8_t pinRead(kbd_gpio_t gpio);

void pinUp(kbd_gpio_t gpio);

void pinDown(kbd_gpio_t gpio);

void KBD_USB_SEND(uint8_t * report);




#endif
