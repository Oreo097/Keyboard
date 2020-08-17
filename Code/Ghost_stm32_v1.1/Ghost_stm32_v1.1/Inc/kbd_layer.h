/*
 * @Descripttion: 储存键层的相关定义
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-08-02 09:34:40
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-08-17 14:10:28
 */ 
#ifndef __KBD_LAYER_H
#define __KBD_LAYER_H

#include "main.h"
#include "kbd_scan.h"

/**
 * @name: Oreo097
 * @msg: 键层的结构体，应该包含，该键层中的fkey的gpio逻辑位置，skey组的逻辑位置组，akey的逻辑位置组
 * @param {type} 
 * @return {type} 
 */
typedef struct
{
     kbd_key_gpio_t fkey;//fkey的逻辑位置
     kbd_key_gpio_t skey[KEY_MAX];
     kbd_key_gpio_t akey[ROW_MAX][COL_MAX];//普通按键的逻辑扫描
}kbd_layer_t;






#endif