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

#ifndef __KBD_FUNC_H
#include "kbd_func.h"
#endif


void KBD_ANS_INIT();

void KBD_SCAN_MAIN();

void test();

void test_free();

void KBD_SCAN_RMJ();



#endif 