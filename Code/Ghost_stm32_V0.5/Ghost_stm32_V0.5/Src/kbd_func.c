/*
 * @Descripttion: 对基础函数二次封装的函数实现
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-07 17:39:38
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-08 11:45:50
 */ 
/**
 * 本文件中的函数是对STM32 HAL库中的底层函数进行二次封装
 * 方便日后移植和修改
 * */




#include "kbd_func.h"
#include <stdbool.h>


extern USBD_HandleTypeDef hUsbDeviceFS;

bool pinRead(kbd_gpio_t gpio)
{
    return HAL_GPIO_ReadPin(gpio.gpio_group,gpio.gpio_pin);
}

void pinUp(kbd_gpio_t gpio)
{
    HAL_GPIO_WritePin(gpio.gpio_group,gpio.gpio_pin,1);
}

void pinDown(kbd_gpio_t gpio)
{
    HAL_GPIO_WritePin(gpio.gpio_group,gpio.gpio_pin,0);
}

void KBD_USB_SEND(uint8_t * report)
{
    USBD_HID_SendReport(&hUsbDeviceFS,report,8);
}
