/*
 * @Descripttion: 本文加主要用于键盘扫描，包含扫描部分，防抖部分，和结果生成和检查部分
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-09 21:15:07
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-09 23:42:29
 */

#include "kbd_scan.h"

kbd_scan_ans_t kbd_scan_ans_1;
kbd_scan_ans_t kdb_scan_ans_2;
kbd_scan_ans_t *ans_1;
kbd_scan_ans_t *ans_2;

extern kbd_map_gpio_t *gpio_map; //来自kbd_param.c的gpio矩阵指针

extern kbd_map_fkey_logic_t *logicmap_fkey; //来自kbd_param.c的逻辑扫描矩阵指针

extern kbd_map_skey_logic_t *logicmap_skey;

extern kbd_map_akey_logic_t *logicmap_akey;

/**
 * @name: Oreo097
 * @msg: 扫描初始化函数，主要用于初始化相关全局变量，本函数主要用于程序启动时的初始化，仅限6KRO使用
 * @param {type} 
 * @return: void
 */
void KBD_SCAN_INIT_6KRO(void)
{
    ans_1 = kbd_scan_ans_1;
    ans_1->number = 1;
    ans_2 = kbd_scan_ans_2;
    ans_2->number = 2;
}

/**
 * @name: Oreo097
 * @msg: 键盘初始化相关函数，用于程序启动的初始化，仅限NKRO
 * @param {type} 
 * @return: void
 */
void KBD_SCAN_INIT_NKRO(void)
{
}

/**
 * @name: Oreo097
 * @msg: 键盘过程中扫描结果刷新函数，用于过程中刷新废弃的扫描结果，仅限6KRO
 * @param {刷新的结果的指针} 
 * @return: 
 */
void KBD_SCAN_REINIT_6KRO(kbd_sacn_ans_t *ans)
{
    ans->index_fkey = 0;
    ans->index_skey = 0;
    ans->index_akey = 0;
    memset(ans->array, 0xff, sizeof(ans->array));
}

/**
 * @name: Oreo097
 * @msg:检查是否是扫描结果中的重复按键的函数 
 * @param {被检查按键的行、列、和答案的指针} 
 * @return: 如果扫描发现在答案中，则返回ture，如果不在答案中返回false
 */
bool KBD_SCAN_CHECK_KEY_6KRO(uint8_t row, uint8_t row, kbd_scan_ans_t *ans)
{
    for (uint8_t index = 0; index < ANS_MAX; index++)
    {
        if (row == ans->array[idnex][0])
        {
            if (col == ans->ans[index][1])
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * @name: Oreo097
 * @msg: 扫描上次的扫描结果，并求出多少个按键空余,并把信息复制到新的ans中,扫描顺序是先扫描功能键（FKEY）在扫描特殊键（SKEY）最后扫描普通键（AKEY）
 * @param {旧的扫描的答案,新的扫描的答案,扫描矩阵} 
 * @return: void
 */
void KBD_SCAN_CALCU_KEY_6KRO(kbd_scan_ans_t *ans1, kbd_scan_ans_t *ans2, kbd_map_gpio_t *gpio_map)
{
#if (FKEY_MAX != 0)
    if (ans1->array[0][0] != 0xff)
    {
        uint8_t index_new_ans = 0;
        for (uint8_t index = 0; index < FKEY_MAX; index++)
        {
            pinUp(gpio_map->gpio_row[ans1->array[index][0]]); //拉高目标行
            if (pinRead(gpio_map->gpio_col[ans1->array[index][0]][ans1->array[index][1]]) == 1)
            {
                ans2->array[index_new_ans][0] == ans1->array[index][0];
                ans2->array[index_new_ans][1] == ans1->array[index][1];
                index_new_ans++;
                ans2->index_fkey++;
            }
        }
    }
#endif
#if (SKEY_MAX != 0)
    if (ans1->array[FKEY_MAX][0] != 0xff)
    {
        uint8_t index_new_ans = FKEY_MAX;
        for (uint8_t index = FKEY_MAX; index < (FKEY_MAX + SKEY_MAX); index++)
        {
            pinUp(gpio_map->gpio_row[ans1->array[index][0]]); //拉高目标行
            if (pinRead(gpio_map->gpio_col[ans1->array[index][0]][ans1->array[index][1]]) == 1)
            {
                ans2->array[index_new_ans][0] == ans1->array[index][0];
                ans2->array[index_new_ans][1] == ans1->array[index][1];
                index_new_ans++;
                ans2->index_skey++;
            }
        }
    }
#endif
#if (AKEY_MAX != 0)
    if (ans1->array[SKEY_MAX][0] != 0xff)
    {
        uint8_t index_new_ans = SKEY_MAX;
        for (uint8_t index = SKEY_MAX; index < (ANS_MAX); index++)
        {
            pinUp(gpio_map->gpio_row[ans1->array[index][0]]); //拉高目标行
            if (pinRead(gpio_map->gpio_col[ans1->array[index][0]][ans1->array[index][1]]) == 1)
            {
                ans2->array[index_new_ans][0] == ans1->array[index][0];
                ans2->array[index_new_ans][1] == ans1->array[index][1];
                index_new_ans++;
                ans2->index_akey++;
            }
        }
    }
#endif
}

#if (FKEY_MAX != 0)
/**
 * @name: Oreo097
 * @msg: 扫描补充功能键（FKEY）函数，主要过程是根据检查结果再扫描相应不在新的ans中的功能按键（FKEY），6KRO专用
 * @param {kbd_map_gpio_t GPIO表，kdb_map_fkey_logic_t fkey的扫描逻辑层，kbd_scan_ans_t * 扫描结果asn的指针} 
 * @return: void
 */
void KBD_SCAN_ADD_FKEY_6KRO(kbd_map_gpio_t *gpio_map, kbd_map_logic_fkey_t *logmap, kbd_scan_ans_t *ans)
{
    for (uint8_t index = 0; index < FKEY_MAX; index++)
    {
        if (ans->index_fkey < FKEY_MAX)
        {
            pinUp(gpio_map->gpio_row[logmap->keymap[index][0]]); //拉高目标行
            if (pinRead(gpio_map->gpio_col[logmap->keymap[index][0]][logmap->keymap]) == true)
            {
                ans->array[ans->index_fkey][0] = logmap->key_map[index][0];
                ans->array[ans->index_fkey][1] = logmap->key_map[index][1];
                ans->index_fkey++;
            }
            pinDown(gpio_map->gpio_row[logmap->keymap[index][0]]); //拉低目标行
        }
        else
        {
            break;
        }
    }
}
#endif

#if(SKEY_MAX!=0)
/**
 * @name: Oreo097
 * @msg:  扫描补充特殊键（SKEY）函数，主要过程是根据检查结果再扫描相应不在新的ans中的功能按键（FKEY），6KRO专用
 * @param {kbd_map_gpio_t GPIO表，kdb_map_skey_logic_t skey的扫描逻辑层，kbd_scan_ans_t * 扫描结果asn的指针} 
 * @return: void
 */
void KBD_SCAN_ADD_SKEY_6KRO(kbd_map_gpio_t *gpio_map, kbd_map_logic_skey_t *logmap, kbd_scan_ans_t *ans)
{
    for (uint8_t index = 0; index < SKEY_MAX; index++)
    {
        if (ans->index_skey < (SKEY_MAX+FKEY_MAX))
        {
            pinUp(gpio_map->gpio_row[logmap->keymap[index][0]]); //拉高目标行
            if (pinRead(gpio_map->gpio_col[logmap->keymap[index][0]][logmap->keymap]) == true)
            {
                ans->array[ans->index_skey][0] = logmap->key_map[index][0];
                ans->array[ans->index_skey][1] = logmap->key_map[index][1];
                ans->index_skey++;
            }
            pinDown(gpio_map->gpio_row[logmap->keymap[index][0]]); //拉低目标行
        }
        else
        {
            break;
        }
    }
}
#endif

#if(SKEY_MAX!=0)
/**
 * @name: Oreo097
 * @msg: 扫描补充普通键（AKEY）函数，主要过程是根据检查结果再扫描相应不在新的ans中的普通按键（AKEY），6KRO专用
 * @param {kbd_map_gpio_t GPIO表，kdb_map_akey_logic_t akey的扫描逻辑层，kbd_scan_ans_t * 扫描结果asn的指针} 
 * @return: void
 */
void KBD_SCAN_ADD_AKEY_6KRO(kbd_map_gpio_t *gpio_map, kbd_map_logic_skey_t *logmap, kbd_scan_ans_t *ans)
{

}
#endif