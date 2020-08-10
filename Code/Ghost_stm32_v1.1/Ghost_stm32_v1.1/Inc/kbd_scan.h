/*
 * @Descripttion: 
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-08-02 09:33:12
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-08-10 22:09:58
 */ 
#ifndef __KBD_SCAN_H
#define __KBD_SCAN_H


#include "kbd_layer.h"
#include "kbd_gpio.h"
#include "main.h"
#include <stdbool.h>
#include "kbd_func.h"

/**
 * @name: Oreo097
 * @msg: 定义键盘相关参数
 * @param {type} 
 * @return {type} 
 */
#define KEY_MAX 17
#define ROW_MAX 5
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
 * @msg: 定义物理键盘的GPIO矩阵
 * @param {type} 
 * @return: 
 */
typedef struct
{
    kbd_gpio_t gpio_row[ROW_MAX];
    uint8_t col_num[ROW_MAX]; //记录每一行有多少个按键的数组
    kbd_gpio_t gpio_col[ROW_MAX][COL_MAX];
}kbd_gpio_map_t;


/**
 * @name: Oreo097
 * @msg: 定义Keyword的类型
 * @param {type} 
 * @return {type} 
 */
typedef uint8_t keyword_t;

/**
 * @name: Oreo097
 * @msg: 功能键的扫描
 * @param {type} 
 * @return: 
 */
typedef struct
{
    uint8_t number;
    uint8_t gpio_map[KEY_MAX][2];//用来储存GPIO扫描的逻辑表
    keyword_t keyword[KEY_MAX];//用来储存键值
}kbd_logicmap_fkey_t;


/**
 * @name: Oreo097
 * @msg: 功能键的扫描结果
 * @param {type} 
 * @return {type} 
 */
typedef struct 
{
    uint8_t index;
    uint8_t ans[KEY_MAX];
}kbd_ans_fkey_t;


/**
 * @name: Oreo097
 * @msg: 定义防抖相关参数
 * @param {type} 
 * @return {type} 
 */
typedef struct 
{
    uint8_t rmj_time;
    uint_
}kbd_scan_config_t;

/**
 * @name: Oreo097
 * @msg: 定义键层结构体
 * @param {type} 
 * @return {type} 
 */
typedef struct
{
    kbd_logicmap_fkey_t fkey_map;
    kbd_ans_fkey_t fkey_ans;
    kbd_logicmap_skey_t skey_map;

    kbd_logicmap_akey_t akey_map;
    
}kbd_keymap_layer_t;

/**
 * @name: Oreo097
 * @msg: 特殊功能键的结构体
 * @param {type} 
 * @return {type} 
 */
typedef struct
{
    uint8_t number;//特殊功能键的个数
    uint8_t gpio_map;[keymax][2];//扫描按键位置的图
    keyword_t keyword[KEY_MAX];//键值
}kbd_logicmap_skey_t;

/**
 * @name: Oreo097
 * @msg: 普通按键结构体
 * @param {type} 
 * @return {type} 
 */
typedef struct
{
    uint8_t row[ROW_MAX];//行
    uint8_t col[ROW_MAX][COL_MAX];//列
    keyword_t keyword[ROW_MAX][COL_MAX];//键值
}kbd_logicmap_akey_t;

#endif