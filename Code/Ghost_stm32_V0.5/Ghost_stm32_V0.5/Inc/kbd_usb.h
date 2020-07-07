/*
 * @Descripttion: USB相关函数
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-01 22:07:59
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-07 21:46:19
 */ 
#ifndef __KBD_USB_H
#define __KBD_USB_H

#ifndef __KBD_INFO_H
#include "kbd_info.h"
#endif

#ifndef __KBD_REPORT_H
#include "kbd_report.h"
#endif


#ifndef __KBD_FUNC_H
#include "kbd_func.h"
#endif

#ifndef __USB_IOREQ_H
#include  "usbd_ioreq.h"
#endif

#ifndef __KBD_INFO_H
#include "kbd_info.h"
#endif

#ifndef __KBD_REPORT_H
#include "kbd_report.h"
#endif

#ifndef __KBD_CONFIG_H
#include "kbd_config.h"
#endif


#define HID_KEYBOARD_REPORT_DESC_SIZE 63U




void KBD_USB_SEND_REPORT(void);









#endif
