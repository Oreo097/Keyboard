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


//kbd_report_t kbd_report;
//kbd_report_t* report;


void KBD_REPORT_MAKE();

void KBD_REPORT_MAIN();

void KBD_REPORT_SEND();


#endif