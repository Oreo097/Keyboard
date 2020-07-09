/*
 * @Descripttion: 此头文件用来定义函数中将会用到的一些数据类型
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-09 11:47:57
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-09 16:50:21
 */

#ifndef __KBD_PARAM_H
#define __KBD_PARAM_H

#include "kbd_func.h"
#include "kbd_config.h"

/**
 * @name: Oreo097
 * @msg:定义GPIO信息的类型 
 * @param {type} 
 * @return: 
 */
typedef struct
{
    GPIO_GROUP *gpio_group; //gpio组
    uint8_t gpio_pin;       //引脚地址偏移量
} kbd_gpio_t;

/**
 * @name: Oreo097
 * @msg: 定义物理gpio矩阵的数据
 * @param {type} 
 * @return: 
 */
typedef struct
{
    kbd_gpio_t gpio_row[ROW_MAX];
    uint8_t col_num[ROW_MAX]; //记录每一行有多少个按键的数组
    kbd_gpio_t gpio_col[ROW_MAX][COL_MAX];
};

/**
 * @name: Oreo097
 * @msg: FKEY逻辑层，主要用来引导程序扫描相应的按键，本逻辑层对应的是GPIO MAP
 * @param {type} 
 * @return: 
 */
#if (FKEY_MAX != 0)
typedef struct
{
    uint8_t key_map[FKEY_MAX][2];
} kbd_map_fkey_t;
#endif

/**
 * @name: Oreo097
 * @msg: SKEY扫描逻辑层，主要用来引导程序扫描相应的按键
 * @param {type} 
 * @return: 
 */
#if (SKEY_MAX != 0)
typedef struct
{
    uint8_t key_map[SKEY_MAX][2];
} kbd_map_skey_t;
#endif

/**
 * @name: Oreo097
 * @msg: AKEY扫描逻辑层，主要用来引导扫描
 * @param {type} 
 * @return: 
 */
#if (AKEY_MAX != 0)
typedef struct
{
    uint8_t num_row[ROW_MAX];
    uint8_t key[ROW_MAX][COL_MAX];

} kbd_map_akey_t;
#endif

#endif
