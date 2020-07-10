/*
 * @Descripttion: 本文加主要用于键盘扫描，包含扫描部分，防抖部分，和结果生成和检查部分
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-09 21:15:07
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-10 23:49:55
 */

#include "kbd_scan.h"

kbd_scan_ans_t kbd_scan_ans_1;
kbd_scan_ans_t kbd_scan_ans_2;
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
    ans_1 = &kbd_scan_ans_1;
    ans_1->number = 1;
    ans_2 = &kbd_scan_ans_2;
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
void KBD_SCAN_REINIT_6KRO(kbd_scan_ans_t *ans)
{
    ans->index_fkey = 0;
    ans->index_skey = FKEY_MAX;
    ans->index_akey = SKEY_MAX + FKEY_MAX;
    memset(ans->array, 0xff, sizeof(ans->array));
    ans->occupied = false;
}

/**
 * @name: Oreo097
 * @msg:检查是否是扫描结果中的重复按键的函数 
 * @param {被检查按键的行、列、和答案的指针} 
 * @return: 如果扫描发现在答案中，则返回ture，如果不在答案中返回false
 */
bool KBD_SCAN_CHECK_KEY_6KRO(uint8_t row, uint8_t col, kbd_scan_ans_t *ans)
{
    for (uint8_t index = 0; index < ANS_MAX; index++)
    {
        if (row == ans->array[index][0])
        {
            if (col == ans->array[index][1])
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
 * @param {kbd_scan_ans_t 旧的扫描的答案,kbd_scan_ans_t 新的扫描的答案,kbd_map_gpio_t 扫描矩阵} 
 * @return: void
 */
void KBD_SCAN_CALCU_KEY_6KRO(kbd_scan_ans_t *ans1, kbd_scan_ans_t *ans2, kbd_map_gpio_t *gpio_map)
{
    //if((ans1->array[0][0]==0xff)&&(ans1->array[FKEY_MAX][0])&&(ans1->array[FKEY_MAX+SKEY_MAX][0]==0xff))
    if (ans1->occupied == false)
    {
        return;
    }
#if (FKEY_MAX != 0)
    if (ans1->array[0][0] != 0xff)
    {
        uint8_t index_new_ans = 0;
        for (uint8_t index = 0; index < FKEY_MAX; index++)
        {
            pinUp(gpio_map->gpio_row[ans1->array[index][0]]); //拉高目标行
            if (pinRead(gpio_map->gpio_col[ans1->array[index][0]][ans1->array[index][1]]) == 1)
            {
                ans2->array[index_new_ans][0] = ans1->array[index][0];
                ans2->array[index_new_ans][1] = ans1->array[index][1];
                index_new_ans++;
                ans2->index_fkey++;
                ans2->occupied=true;
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
                ans2->array[index_new_ans][0] = ans1->array[index][0];
                ans2->array[index_new_ans][1] = ans1->array[index][1];
                index_new_ans++;
                ans2->index_skey++;
                ans2->occupied=true;
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
                ans2->array[index_new_ans][0] = ans1->array[index][0];
                ans2->array[index_new_ans][1] = ans1->array[index][1];
                index_new_ans++;
                ans2->index_akey++;
                ans2->occupied=true;
            }
        }
    }
#endif
}

/**
 * @name: Oreo097
 * @msg: 扫描补充功能键（FKEY）函数，主要过程是根据检查结果再扫描相应不在新的ans中的功能按键（FKEY），6KRO专用
 * @param {kbd_map_gpio_t GPIO表，kdb_map_fkey_logic_t fkey的扫描逻辑层，kbd_scan_ans_t * 扫描结果asn的指针} 
 * @return: void
 */
void KBD_SCAN_ADD_FKEY_6KRO(kbd_map_gpio_t *gpio_map, kbd_map_fkey_logic_t *logmap, kbd_scan_ans_t *ans)
{
#if (FKEY_MAX != 0)
    for (uint8_t index = 0; index < FKEY_MAX; index++)
    {
        if (ans->index_fkey < FKEY_MAX)
        {
            pinUp(gpio_map->gpio_row[logmap->key_map[index][0]]); //拉高目标行
            if (pinRead(gpio_map->gpio_col[logmap->key_map[index][0]][logmap->key_map[index][1]]) == true)
            {
                if (KBD_SCAN_CHECK_KEY_6KRO(logmap->key_map[index][0], logmap->key_map[index][1],ans) != true)
                {
                    ans->array[ans->index_fkey][0] = logmap->key_map[index][0];
                    ans->array[ans->index_fkey][1] = logmap->key_map[index][1];
                    ans->index_fkey++;
                    ans->occupied = true;
                }
            }
            pinDown(gpio_map->gpio_row[logmap->key_map[index][0]]); //拉低目标行
        }
        else
        {
            break;
        }
    }
#endif
}

/**
 * @name: Oreo097
 * @msg:  扫描补充特殊键（SKEY）函数，主要过程是根据检查结果再扫描相应不在新的ans中的功能按键（FKEY），6KRO专用
 * @param {kbd_map_gpio_t GPIO表，kdb_map_skey_logic_t skey的扫描逻辑层，kbd_scan_ans_t * 扫描结果asn的指针} 
 * @return: void
 */
void KBD_SCAN_ADD_SKEY_6KRO(kbd_map_gpio_t *gpio_map, kbd_map_skey_logic_t *logmap, kbd_scan_ans_t *ans)
{
#if (SKEY_MAX != 0)
    for (uint8_t index = 0; index < SKEY_MAX; index++)
    {
        if (ans->index_skey < (SKEY_MAX + FKEY_MAX))
        {
            pinUp(gpio_map->gpio_row[logmap->key_map[index][0]]); //拉高目标行
            if (pinRead(gpio_map->gpio_col[logmap->key_map[index][0]][logmap->key_map[index][1]]) == true)
            {
                if (KBD_SCAN_CHECK_KEY_6KRO(logmap->key_map[index][0], logmap->key_map[index][1],ans) != true)
                {
                    ans->array[ans->index_skey][0] = logmap->key_map[index][0];
                    ans->array[ans->index_skey][1] = logmap->key_map[index][1];
                    ans->index_skey++;
                    ans->occupied = true;
                }
            }
            pinDown(gpio_map->gpio_row[logmap->key_map[index][0]]); //拉低目标行
        }
        else
        {
            break;
        }
    }
#endif
}

/**
 * @name: Oreo097
 * @msg: 扫描补充普通键（AKEY）函数，主要过程是根据检查结果再扫描相应不在新的ans中的普通按键（AKEY），6KRO专用
 * @param {kbd_map_gpio_t GPIO表，kdb_map_akey_logic_t akey的扫描逻辑层，kbd_scan_ans_t * 扫描结果asn的指针} 
 * @return: void
 */
void KBD_SCAN_ADD_AKEY_6KRO(kbd_map_gpio_t *gpio_map, kbd_map_akey_logic_t *logmap, kbd_scan_ans_t *ans)
{
#if (AKEY_MAX != 0)
    for (uint8_t index_row = 0; index_row < ROW_MAX; index_row++)
    {
        if (logmap->num_row[index_row] == 0xFF)
        {
            continue; //如果这一行普通键（AKEY）个数为0，跳过本次循环
        }
        pinUp(gpio_map->gpio_row[index_row]);
        for (uint8_t index_col = 0; index_col < COL_MAX; index_col++)
        {
            if ((ans->index_akey) > ANS_MAX)
            {
                pinDown(gpio_map->gpio_row[index_row]);
                return;
            }
            if (pinRead(gpio_map->gpio_col[index_row][logmap->key_map[index_row][index_col]]) == true)
            {
                if (KBD_SCAN_CHECK_KEY_6KRO(index_row, logmap->key_map[index_row][index_col],ans) != true)
                {
                    ans->array[ans->index_akey][0] = index_row;
                    ans->array[ans->index_akey][1] = logmap->key_map[index_row][index_col];
                    ans->index_akey++;
                    ans->occupied = true;
                }
            }
        }
        pinDown(gpio_map->gpio_row[index_row]);
    }
#endif
}

/**
 * @name: Oreo097
 * @msg: 扫描的主逻辑函数，主要用于扫描键盘的GIPIO矩阵，并生成扫描结果，采用两个扫描结果交替记录的方式，这样可以高效的相互对照
 * @param {void} 
 * @return: void
 */
void KBD_SCAN_MAIN(void)
{
#if (NKRO_MODE == 0)
    if (ans_1->occupied == true) //检查0xff是不是空的，如果是空的就用
    {
        //KBD_SCAN_REINIT_6KRO(ans_1);//初始化ans_1
        KBD_SCAN_CALCU_KEY_6KRO(ans_2, ans_1, gpio_map);
        KBD_SCAN_REINIT_6KRO(ans_2);
        if (ans_1->index_fkey != FKEY_MAX)
        {
            KBD_SCAN_ADD_FKEY_6KRO(gpio_map, logicmap_fkey, ans_1);
        }
        if (ans_1->index_skey != (FKEY_MAX + SKEY_MAX))
        {
            KBD_SCAN_ADD_SKEY_6KRO(gpio_map, logicmap_skey, ans_1);
        }
        if (ans_1->index_akey != ANS_MAX)
        {
            KBD_SCAN_ADD_AKEY_6KRO(gpio_map, logicmap_akey, ans_1);
        }
    }
    else
    {
        //KBD_SCAN_REINIT_6KRO(ans_2);//初始化ans_2
        KBD_SCAN_CALCU_KEY_6KRO(ans_1, ans_2, gpio_map);
        KBD_SCAN_REINIT_6KRO(ans_1);
        if (ans_2->index_fkey != FKEY_MAX)
        {
            KBD_SCAN_ADD_FKEY_6KRO(gpio_map, logicmap_fkey, ans_2);
        }
        if (ans_2->index_skey != (FKEY_MAX + SKEY_MAX))
        {
            KBD_SCAN_ADD_SKEY_6KRO(gpio_map, logicmap_skey, ans_2);
        }
        if (ans_2->index_akey != ANS_MAX)
        {
            KBD_SCAN_ADD_AKEY_6KRO(gpio_map, logicmap_akey, ans_2);
        }
    }
#else
#endif
}
