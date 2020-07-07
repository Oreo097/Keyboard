/*
 * @Descripttion: 
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-07 17:39:38
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-07 19:28:34
 */ 
/**
 * USB功能实现
 * 包括HID report发送
 * */

#include "kbd_usb.h"

// __ALIGN_BEGIN static uint8_t HID_KEYBOARD_ReportDesc[HID_KEYBOARD_REPORT_DESC_SIZE]  __ALIGN_END =
// {
// 0x05, 0x01,// USAGE_PAGE (Generic Desktop)
// 0x09, 0x06,// USAGE (Keyboard)
// 0xa1, 0x01,// COLLECTION (Application)
// 0x05, 0x07,//USAGE_PAGE (Keyboard)
// 0x19, 0xe0,//SAGE_MINIMUM (Keyboard LeftControl)
// 0x29, 0xe7,//USAGE_MAXIMUM (Keyboard Right GUI)
// 0x15, 0x00,//LOGICAL_MINIMUM (0)
// 0x25, 0x01,//LOGICAL_MAXIMUM (1)
// 0x75, 0x01,//REPORT_SIZE (1)
// 0x95, 0x08,//REPORT_COUNT (8)
// 0x81, 0x02,//INPUT (Data,Var,Abs)
// 0x95, 0x01,//REPORT_COUNT (1)
// 0x75, 0x08,//REPORT_SIZE (8)
// 0x81, 0x03,//INPUT (Cnst,Var,Abs)
// 0x95, 0x05,//REPORT_COUNT (5)
// 0x75, 0x01,//REPORT_SIZE (1)
// 0x05, 0x08,//USAGE_PAGE (LEDs)
// 0x19, 0x01,//USAGE_MINIMUM (Num Lock)
// 0x29, 0x05,//USAGE_MAXIMUM (Kana)
// 0x91, 0x02,//OUTPUT (Data,Var,Abs)
// 0x95, 0x01,//REPORT_COUNT (1)
// 0x75, 0x03,//REPORT_SIZE (3)
// 0x91, 0x03,//OUTPUT (Cnst,Var,Abs)
// 0x95, 0x06,//REPORT_COUNT (6)
// 0x75, 0x08,//REPORT_SIZE (8)
// 0x15, 0x00,//LOGICAL_MINIMUM (0)
// 0x25, 0xFF,//LOGICAL_MAXIMUM (255)
// 0x05, 0x07,//USAGE_PAGE (Keyboard)
// 0x19, 0x00,//USAGE_MINIMUM (Reserved (no event indicated))
// 0x29, 0x65,//USAGE_MAXIMUM (Keyboard Application)
// 0x81, 0x00,//INPUT (Data,Ary,Abs)
// 0xc0
// };

extern kbd_report_t kbd_report[REPORT_MAX];

//发送报告的函数，把报告通过USB发送到上机位
void KBD_USB_SEND_REPORT(void)
{
#ifdef DBG_MODE
    printf("send report!\n");
#endif
    report_keyword(kbd_report);
    KBD_USB_SEND(kbd_report);
#ifdef DBG_MODE
    printf("send complete!\n");
#endif
    KBD_REPORT_INIT();
}
