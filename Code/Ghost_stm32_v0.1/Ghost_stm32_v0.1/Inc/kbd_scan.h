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


void KBD_ANS_INIT(void);

void KBD_SCAN_MAIN(void);

void test(void);

void test_free(void);

void KBD_SCAN_RMJ(void);

void KBD_SCAN_SKEY(void);

void KBD_SCAN_AKEY(void);

void KBD_SCAN_FKEY(void);

void KBD_SCAN_GETGPIO(void);

#endif 
