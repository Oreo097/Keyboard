#include "kbd_func.h"

extern USBD hUsbDeviceFS;

/**
 * @name: Oreo097
 * @msg: 读取引脚电平
 * @param {kbd_gpio_t GPIO} 
 * @return: 
 */
bool pinRead(kbd_gpio_t gpio)
{
    return HAL_GPIO_ReadPin(gpio.gpio_group,gpio.gpio_pin);
}

/**
 * @name: Oreo097
 * @msg: 拉高引脚
 * @param {type} 
 * @return: 
 */
void pinUp(kbd_gpio_t gpio)
{
    HAL_GPIO_WritePin(gpio.gpio_group,gpio.gpio_pin,1);
}

/**
 * @name: Oreo097
 * @msg: 拉低引脚
 * @param {type} 
 * @return: 
 */
void pinDown(kbd_gpio_t gpio)
{
    HAL_GPIO_WritePin(gpio.gpio_group,gpio.gpio_pin,0);
}

/**
 * @name: Oreo097
 * @msg: USB HID 发送数据
 * @param {type} 
 * @return: 
 */
// void KBD_USB_SEND(uint8_t * report)
// {
//     USBD_HID_SendReport(&hUsbDeviceFS,report,8);
// }

/**
 * @name: Oreo097
 * @msg: 实现memset函数
 * @param {type} 
 * @return: 
 */
void* memset(void* s, int c, size_t n)
{
    unsigned char* p = (unsigned char*) s;

    while (n > 0) {
    *p++ = (unsigned char) c;
    --n;
    }

    return s;
}

