/*
 * @Descripttion: 本文件主要用来组成输出相关reprot
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-11 16:27:49
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-28 21:51:29
 */ 
#ifndef __KBD_REPORT_H
#define __KBD_REPORT_H

#include "kbd_config.h"
#include "kbd_param.h"
#include "kbd_scan.h"
#include "kbd_debug.h"

#include <stdbool.h>



bool KBD_REPORT_CHECK_ANS(kbd_scan_ans_t * ans);

void KBD_REPROT_MAKE_6KRO(kbd_scan_ans_t * ans,kbd_map_keywords_t keyword);

void KBD_REPROT_MAKE_SKEY_6KRO(kbd_scan_ans_t * ans,kbd_map_keywords_t * keyword,kbd_report_t * report);

void KBD_REPORT_MAKE_AKEY_6KRO(kbd_scan_ans_t * ans,kbd_map_keywords_t * keyword,kbd_report_t * report);

void KBD_REPORT_KMAP_SWITCH_6KRO(kbd_scan_ans_t * ans,kbd_map_keywords_t keyword,kbd_report_t * report);

void KBD_REPORT_KEMAP_SWITCHS_6KRO(kbd_scan_ans_t * ans,kbd_map_keywords_t * keyword,kbd_report_t * report);

void KBD_REPORT_SEND(kbd_report_t report);

void KBD_REPORT_MAIN(void);




#endif
