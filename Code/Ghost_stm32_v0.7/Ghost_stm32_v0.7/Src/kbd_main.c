/*
 * @Descripttion: 
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-08-02 08:33:30
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-08-02 09:07:38
 */ 


#include "kbd_main.h"


extern kbd_scan_ans_t * ans_1;

extern kbd_scan_ans_t * ans_2;

extern kbd_map_gpio_t *gpio_map; //来自kbd_param.c的gpio矩阵指针

extern kbd_map_fkey_logic_t *logicmap_fkey; //来自kbd_param.c的逻辑扫描矩阵指针

extern kbd_map_skey_logic_t *logicmap_skey;

extern kbd_map_akey_logic_t *logicmap_akey;




void KBD_MAIN(void)
{
    KBD_SCAN_INIT_6KRO();
    while(true)
    {
        if(ans_1-> occupied==true)
        {
            KBD_SCAN_CALU_KEY_6KRO(ans_1,ans_2,gpio_map);
        }
        else
        {
            KBD_SCAN_CALU_KEY_6KRO(ans_2,ans_1,gpio_map);
        }
    }
}