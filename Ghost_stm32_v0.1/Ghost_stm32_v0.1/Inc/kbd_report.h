#ifndef __KBD_KEYWORD_H
#define __KBD_KEYWORD_H

#ifndef __KBD_INFO_H
#include "kbd_info.h"
#endif 

#ifndef __MAIN_H
#include "main.h"
#endif


#ifndef __KBD_SCAN_H
#include "kbd_scan.h"
#endif


kbd_report_t kbd_report;
kbd_report_t* report;

extern kbd_ans_t* ans;//pointer for kbd_ans come form kbd_scan

void KBD_REPORT_USB_INIT();

void KBD_REPORT_MAKE();



#endif