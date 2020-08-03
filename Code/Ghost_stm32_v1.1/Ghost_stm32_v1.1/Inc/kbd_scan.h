/*
 * @Descripttion: 
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-08-02 09:33:12
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-08-02 09:56:53
 */ 
#ifndef __KBD_SCAN_H
#define __KBD_SCAN_H


#include "kbd_layer.h"
#include "kbd_gpio.h"
#include "main.h"



/**
 * @name: Oreo097
 * @msg: 定义键盘的行数
 * @param {type} 
 * @return: 
 */
#define ROW_MAX 5

/**
 * @name: Oreo097
 * @msg: 定义键盘的列数
 * @param {type} 
 * @return: 
 */
#define COL_MAX 4


/**
 * @name: Oreo097
 * @msg:定义GPIO信息的类型 
 * @param {type} 
 * @return: 
 */
#define GPIO_GROUP GPIO_TypeDef //GPIO组的数据类型
typedef struct kbd_gpio
{
    GPIO_GROUP *gpio_group; //gpio组
    uint8_t gpio_pin;       //引脚地址偏移量
} kbd_gpio_t;


/**
 * @name: Oreo097
 * @msg: 
 * @param {type} 
 * @return: 
 */
typedef struct kbd_gpio_map
{
    kbd_gpio_t gpio_row[ROW_MAX];
    uint8_t col_num[ROW_MAX]; //记录每一行有多少个按键的数组
    kbd_gpio_t gpio_col[ROW_MAX][COL_MAX];
}kbd_gpio_map_t;


#endif