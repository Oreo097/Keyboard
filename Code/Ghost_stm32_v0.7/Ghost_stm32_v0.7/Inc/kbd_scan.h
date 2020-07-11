/*
 * @Descripttion: 主要用于扫描的头文件
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-09 21:14:12
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-11 09:44:55
 */ 


#ifndef __KBD_SCAN_H
#define __KBD_SCAN_H
#include <stdbool.h>
#include "kbd_param.h"
#include "kbd_func.h"





void KBD_SCAN_INIT_6KRO(void);

void KBD_SCAN_INIT_NKRO(void);

void KBD_SCAN_REINIT_6KRO(kbd_scan_ans_t *ans);

bool KBD_SCAN_CHECK_KEY_6KRO(uint8_t row, uint8_t col, kbd_scan_ans_t *ans);

void KBD_SCAN_CALCU_KEY_6KRO(kbd_scan_ans_t *ans1, kbd_scan_ans_t *ans2, kbd_map_gpio_t *gpio_map);

void KBD_SCAN_ADD_FKEY_6KRO(kbd_map_gpio_t *gpio_map, kbd_map_fkey_logic_t *logmap, kbd_scan_ans_t *ans);

void KBD_SCAN_ADD_SKEY_6KRO(kbd_map_gpio_t *gpio_map, kbd_map_skey_logic_t *logmap, kbd_scan_ans_t *ans);

void KBD_SCAN_ADD_AKEY_6KRO(kbd_map_gpio_t *gpio_map, kbd_map_akey_logic_t *logmap, kbd_scan_ans_t *ans);

void KBD_SCAN_MAIN(void);

void KBD_SCAN_RMJ(kbd_map_gpio_t *gpio_map, kbd_scan_ans_t *ans);

#endif
