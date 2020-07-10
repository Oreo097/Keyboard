/*
 * @Descripttion: 本头文件用来储存一些定义键盘设置的参数
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-09 11:49:24
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-10 11:44:09
 */ 
#ifndef __KBD_CONFIG_H
#define __KBD_CONFIG_H

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
 * @msg: 定义键盘的6键无冲模式的回报长度
 * @param {type} 
 * @return: 
 */
#define REPORT_MAX_6 8

/**
 * @name: Oreo097
 * @msg: 定义全键无冲的回报长度
 * @param {type} 
 * @return: 
 */
#define REPORT_MAX_N 128

/**
 * @name: Oreo097
 * @msg: 定义功能键（FKEY）的个数
 * @param {type} 
 * @return: 
 */
#define FKEY_MAX 1

/**
 * @name: Oreo097
 * @msg: 定义特殊按键（SKEY）的个数
 * @param {type} 
 * @return: 
 */
#define SKEY_MAX 1

/**
 * @name: Oreo097
 * @msg: 定义普通按键（AKEY）个数
 * @param {type} 
 * @return: 
 */
#define AKEY_MAX 1

/**
 * @name: Oreo097
 * @msg:键盘全键无冲模式开关 
 * @param {type} 
 * @return:1为开，0为关 
 */
#define NKRO_MODE 0

#endif