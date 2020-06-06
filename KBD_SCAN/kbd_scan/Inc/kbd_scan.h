/*
 * @Author: your name
 * @Date: 2020-06-03 21:47:05
 * @LastEditTime: 2020-06-06 17:56:16
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \kbd_scan\Inc\kbd_scan.h
 */
#ifndef __KBD_SCAN_H
#define __KBD_SCAN_H

#ifndef __MAIN_H
#include "main.h"
#endif

#ifndef __KBD_INFO_H
#include "kbd_info.h"
#endif

//声明反馈值结构
answer_t answer;
//声明键盘信息结构
kbd_info_t kbd_info;

//反馈值结构的指针
//answer_t * answer_ptr=answer;

//键盘扫描函数初始化
void KBD_SCAN_INIT(kbd_info_t mykbd_info);
//键盘扫描开始
void KBD_SCAN_START();
//键盘扫描结束
void KBD_SCAN_STOP();

//键盘扫描频率中断初始化
void KBD_SCAN_SCAN_TIM_INIT(tim_info_t m_timer);
//键盘扫描频率中断开始
void KBD_SCAN_SCAN_TIM_START();
//键盘扫描频率中断停止
void KBD_SCAN_SCAN_TIM_STOP();

//键盘去抖中断初始化
void KBD_SCAN_RMJIT_TIM_INIT(tim_info_t m_timer);
//键盘去抖中断开始
void KBD_SCAN_RMJIT_TIM_START();
//键盘去抖中断重载
void KBD_SCAN_RMJIT_TIM_RELOAD(tim_info_t m_timer);
//键盘去抖中断停止
void KBD_SCAN_RMJIT_TIM_STOP();

/**
 * 键盘扫描主要逻辑算法
 * */
//整体扫描算法
uint8_t KBD_SCAN_SCAN_MAIN(keymap_phy_t m_keymap_phy);

//扫描一行的算法
uint8_t KBD_SCAN_SCAN_ROW(gpio_t *gpio_map_col, uint8_t col_num,uint8_t row_now);

//扫描单独一个按键，防抖用
uint8_t KBD_SCAN_SCAN_EACH(gpio_t *m_answer);

/**
 * 防抖逻辑算法
 * */

void KBD_SCAN_RMJIT_MAIN();

/**
 * 重写GPIO操作函数
 * 移植时请重写
 * */

//拉高GPIO
void KBD_SCAN_GPIO_UP(gpio_t * m_gpio);

//拉低GPIO
void KBD_SCAN_GPIO_DW(gpio_t * m_gpio);

//读取GPIO
uint8_t KBD_SCAN_GPIO_READ(gpio_t * m_gpio);

#endif