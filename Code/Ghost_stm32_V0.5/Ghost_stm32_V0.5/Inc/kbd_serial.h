/*
 * @Descripttion: 串口函数，用来debug
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-01 22:07:59
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-07 19:28:07
 */ 
#ifndef __KBD_SERIAL_H
#define __KBD_SERIAL_H

#ifndef __USART_H
#include "usart.h"
#endif

#ifndef __MAIN_H
#include "main.h"
#endif

#ifndef __KBD_INFO_H
#include "kbd_info.h"
#endif

#ifndef _STDIO_H_
#include "stdio.h"
#endif


#ifndef __KBD_CONFIG_H
#include "kbd_config.h"
#endif

#define send(words) HAL_UART_Transmit(&huart1,(words),sizeof((words)),100)


void report_map(kbd_ans_t * ans);

uint8_t itoc(uint8_t unm);

void report_key(uint8_t row,uint8_t col,uint8_t status);

void report_rm(uint8_t row, uint8_t col);

void report_keyword(kbd_report_t * report);



#endif
