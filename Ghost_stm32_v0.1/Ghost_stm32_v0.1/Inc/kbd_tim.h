#ifndef __KBD_TIM_H
#define __KBD_TIM_H

#ifndef __MAIN_H
#include "main.h"
#endif

#ifndef __KBD_INFO_H
#include "kbd_info.h"
#endif


#define TIM_SCAN htim1

#define TIM_RMJ htim2

kbd_tim_t kbd_scan_tim;

kbd_tim_t kbd_rmj_tim;


void KBD_TIM_INIT(kbd_tim_t * timer);











#endif