#include "kbd_func.h"


uint8_t pinRead(kbd_gpio_t gpio)
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

