/*
 * @Descripttion: 用来使用串口输出相关的信息的debug文件
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-10 15:57:05
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-08-02 09:17:45
 */ 
#ifndef __KBD_DEBUG_H
#define __KBD_DEBUG_H

#include "main.h"
#include "kbd_param.h"
#include <stdbool.h>
#include "kbd_config.h"
#include <stdlib.h>

#include "usart.h"

/**
 * @name: Oreo097
 * @msg: 使用宏函数，定义发送的数据类型
 * @param {type} 
 * @return: 
 */
#define send(words) HAL_UART_Transmit(&UART_DBG,(words),sizeof((words)),100)

/**
 * @name: Oreo097
 * @msg: 宏函数定义输出函数名的函数
 * @param {type} 
 * @return: 
 */
#define KBD_SEND_FUNC_NAME() printf("%s: ",__func__)

void KBD_DBG_KEY(uint8_t row, uint8_t col, bool status);

void KBD_DBG_ANS_6KRO(kbd_scan_ans_t *ans);

void KBD_DBG_RMJ(uint8_t row, uint8_t col);

void KBD_DBG_REP_6KRO(uint8_t *report);

void KBD_DBG_SCAN_CALU_NUM(uint8_t row,uint8_t col);

#endif
