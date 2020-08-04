/*
 * @Descripttion: 
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-08-02 09:33:12
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-08-04 10:29:33
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
 * @msg: 
 * @param {type} 
 * @return {type} 
 */
#define KEY_MAX 17

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
 * @msg: 
 * @param {type} 
 * @return {type} 
 */
typedef struct 
{
    uint8_t rmj_time;
}kbd_scan_config_t;




#endif