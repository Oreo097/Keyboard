/*
 * @Descripttion: 这是键盘扫描的功能模块，包含相关函数的定义和相关主要逻辑
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-08-05 06:52:20
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-08-17 13:45:10
 */

#include "kbd_scan.h"
#include "kbd_func.h"

extern kbd_gpio_map_t *gpio_map;

/**
 * @name: Oreo097
 * @msg: 键盘扫描额主要逻辑
 * @param {type} 
 * @return {type} 
 */
void KBD_SCAN_MAIN()
{
    /**
     * 扫描的主要逻辑如下
     * 先扫描第一个键层的功能键（目前只设计一个功能键）
     * 如果功能按键被按下
     * 延迟防抖
     * 扫描第二个键层的特殊键
     * 扫描第二个键层的普通键
     * 延迟防抖
     * 如果第一个键层的功能键没有被按下
     * 扫描第一个键层的特殊键
     * 扫描第一个键层的普通键
     * 延迟防抖
     * 生成报告
     * 发送报告
     */
}

/**
 * @name: Oreo097
 * @msg: 扫描单个按键的函数
 * @param {kbd_key_gpio_t key 要检测单个按键的GPIO信息} 
 * @return {bool，如果按下则返回true，如果没按下则返回false} 
 */
bool KBD_SCAN_ONEKEY(kbd_key_gpio_t *key)
{
    pinUp(gpio_map->gpio_row[key->row]);
    if (pinRead(gpio_map->gpio_col[key->row][key->col]) == 1)
    {
        pinDown(gpio_map->gpio_row[key->row]);
        return true;
    }
    return false;
}

/**
 * @name: Oreo097
 * @msg: 扫描第一个键层的FKEY
 * @param {kbd_logicmap_fkey_t * key_logicmap,要扫描按键的逻辑扫描表} 
 * @return {void} 
 */
void KBD_SCAN_FKEY(kbd_logicmap_group_t *logicmap)
{
    if (KBD_SCAN_ONEKEY(&logicmap->gpio_map[0]) == true) //目前只使用扫描一个按键的功能
    {
        //切换键层
        return;
    }
}

/**
 * @name: Oreo097
 * @msg: 扫描SKEY
 * @param {kbd_logicmap_sgroup_t * logicmap SKEY的逻辑扫描图} 
 * @return {kbd_ans_skey_t} 
 */
kbd_ans_t KBD_SCAN_SKEY(kbd_logicmap_group_t *logicmap)
{
    kbd_ans_t ans;
    ans.index = 0;
    for (uint8_t index; index < logicmap->number; index++)
    {
        pinUp(gpio_map->gpio_row[logicmap->gpio_map[index].row]);
        if (pinRead(gpio_map->gpio_col[logicmap->gpio_map[index].row][logicmap->gpio_map[index].col]) == 1)
        {
            KBD_DELAY(1);//防抖延迟1ms
            if (pinRead(gpio_map->gpio_col[logicmap->gpio_map[index].row][logicmap->gpio_map[index].col]) == 1)
            {
                //生成报告
                ans.ans[ans.index] = logicmap->keyword[index];
                ans.index++;
            }
        }
        pinDown(gpio_map->gpio_row[logicmap->gpio_map[index].row]);
    }
    return ans;
}

/**
 * @name: Oreo097
 * @msg: 扫描普通按键
 * @param {type} 
 * @return {type} 
 */
kbd_ans_t KBD_SCAN_AKEY(kbd_logicmap_matrix_t *logicmap)
{
    kbd_ans_t ans;
    ans.index=0;
    for (uint8_t index; index < ROW_MAX; index++)
    {
        pinUp(gpio_map->gpio_row[index]);
        for (uint8_t index_col; index_col < logicmap->col_number[index]; index++)
        {
            if (pinRead(gpio_map->gpio_col[logicmap->col[index][index_col].row][logicmap->col[index][index_col].col])==1)
            {
                KBD_DELAY(1);//防抖延迟1ms
                if (pinRead(gpio_map->gpio_col[logicmap->col[index][index_col].row][logicmap->col[index][index_col].col])==1)
                {
                    ans.ans[ans.index]=logicmap->keyword[index][index_col];
                    ans.index++;
                }
            }
        }
        pinDown(gpio_map->gpio_row[index]);
    }
    return ans;
}

