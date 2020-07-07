/*
 * @Descripttion: 
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-01 22:07:59
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-07 19:28:09
 */ 
#ifndef __KBD_TIM_H
#define __KBD_TIM_H

#ifndef __MAIN_H
#include "main.h"
#endif

#ifndef __KBD_INFO_H
#include "kbd_info.h"
#endif

#ifndef __TIM_H
#include "tim.h"
#endif


#ifndef __KBD_CONFIG_H
#include "kbd_config.h"
#endif

#define TIM_SCAN htim1

#define TIM_RMJ htim2


void KBD_TIM1_INIT(kbd_tim_t * timer);

void KBD_TIM1_INIT(kbd_tim_t * timer);









#endif
