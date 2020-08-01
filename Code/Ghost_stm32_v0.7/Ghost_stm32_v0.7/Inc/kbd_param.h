/*
 * @Descripttion: 此头文件用来定义函数中将会用到的一些数据类型
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-09 11:47:57
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-08-01 21:10:53
 */

#ifndef __KBD_PARAM_H
#define __KBD_PARAM_H

#include "main.h"
#include "kbd_config.h"
#include "kbd_gpio.h"
#include "usb_device.h"
#include "kbd_keyword.h"

#include <stdbool.h>

#define USBD USBD_HandleTypeDef //usb的数据类型
#define GPIO_GROUP GPIO_TypeDef //GPIO组的数据类型

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
} kbd_map_gpio_t;

/**
 * @name: Oreo097
 * @msg: FKEY逻辑层，主要用来引导程序扫描相应的按键，本逻辑层对应的是GPIO MAP
 * @param {type} 
 * @return: 
 */
typedef struct
{
    uint8_t key_numb; //存储按键数量
    uint8_t key_map[KEY_MAX][2];
} kbd_map_fkey_logic_t;

/**
 * @name: Oreo097
 * @msg: SKEY扫描逻辑层，主要用来引导程序扫描相应的按键
 * @param {type} 
 * @return: 
 */
typedef struct
{
    uint8_t key_numb; //用来存储按键数量
    uint8_t key_map[KEY_MAX][2];
} kbd_map_skey_logic_t;

/**
 * @name: Oreo097
 * @msg: AKEY扫描逻辑层，主要用来引导扫描
 * @param {type} 
 * @return: 
 */
typedef struct
{
    uint8_t key_numb;
    uint8_t num_row[ROW_MAX];
    uint8_t key_map[ROW_MAX][COL_MAX];

} kbd_map_akey_logic_t;

/**
 * @name: Oreo097
 * @msg: 定义扫描结果的结构体，主要用于存储扫描结果方便后边生成report
 * @param {前FKEY_MAX个是功能键扫描结果，中间SKEY_MAX个是特殊键扫描结果，后边REPORT_MAX-2个是普通按键扫描结果} 
 * @return: 
 */
typedef struct
{
    bool occupied;
    bool changed;
    uint8_t number;
    uint8_t fkey_array[KEY_MAX][2];
    uint8_t skey_array[KEY_MAX][2];
    uint8_t akey_array[KEY_MAX][2];
    uint8_t index_fkey;
    uint8_t index_skey;
    uint8_t index_akey;
} kbd_scan_ans_t;

/**
 * @name: Oreo097
 * @msg: 按键的键值矩阵类型，用来从中找出对应的键值
 * @param {type} 
 * @return: 
 */
typedef uint8_t kbd_map_keyword_t;
typedef struct
{
    kbd_map_keyword_t keymap[ROW_MAX][COL_MAX];
} kbd_map_keywords_t;

/**
 * @name: Oreo097
 * @msg: 按键报告的定义
 * @param {type} 
 * @return: 
 */
typedef uint8_t kbd_report_t;

#endif
