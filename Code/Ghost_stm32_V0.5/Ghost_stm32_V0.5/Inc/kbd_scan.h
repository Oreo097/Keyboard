/*
 * @Descripttion: 键盘扫描的相关函数
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-01 22:07:59
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-08 11:30:52
 */
#ifndef __KBD_SCAN_H
#define __KBD_SCAN_H

#ifndef __MAIN_H
#include "main.h"
#endif

#ifndef __KBD_INFO_H
#include "kbd_info.h"
#endif

#ifndef __KBD_SERIAL_H
#include "kbd_serial.h"
#endif

#ifndef __KBD_REPORT_H
#include "kbd_report.h"
#endif

#ifndef __KBD_FUNC_H
#include "kbd_func.h"
#endif

#ifndef __KBD_USB_H
#include "kbd_usb.h"
#endif

#ifndef __KBD_CONFIG_H
#include "kbd_config.h"
#endif


void KBD_SCAN_ANS_INIT(void);

void KBD_SCAN_ANS_REINIT(void);

void KBD_SCAN_MAIN(void);

void test(void);

void test_free(void);

void KBD_SCAN_RMJ(void);

#if (NUM_AKEY != 0)
void KBD_SCAN_AKEY(void);
#endif

#if (NUM_FKEY != 0)
void KBD_SCAN_FKEY(void);
#endif

#if (NUM_SKEY != 0)
void KBD_SCAN_SKEY(void);
#endif

void KBD_SCAN_GETGPIO(void);

void KBD_SCAN_ANS(void);

#endif
