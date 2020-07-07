/*
 * @Descripttion: 与hid相关的报告
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-01 22:07:59
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-07 21:39:58
 */ 
#ifndef __KBD_KEYWORD_H
#define __KBD_KEYWORD_H


#ifndef __KBD_CONFIG_H
#include "kbd_config.h"
#endif

#ifndef __KBD_INFO_H
#include "kbd_info.h"
#endif 

#ifndef __MAIN_H
#include "main.h"
#endif


#ifndef __KBD_SCAN_H
#include "kbd_scan.h"
#endif


//kbd_report_t kbd_report;
//kbd_report_t* report;


void KBD_REPORT_MAKE(void);

void KBD_REPORT_MAIN(void);

//void KBD_REPORT_SEND(void);

void KBD_REPORT_INIT(void);

#endif
