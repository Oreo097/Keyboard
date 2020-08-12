/*
 * @Descripttion: 键盘的按键扫描部分
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-08-02 09:33:05
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-08-11 20:11:52
 */

#include "kbd_scan.h"

kbd_gpio_map_t kbd_gpio_map = {
    {{ROW0_G, ROW0_P}, {ROW1_G, ROW1_P}, {ROW2_G, ROW2_P}, {ROW3_G, ROW3_P}, {ROW4_G, ROW4_P}},
    {4,
     4,
     3,
     4,
     2},
    {{{COL0_G, COL0_P}, {COL1_G, COL1_P}, {COL2_G, COL2_P}, {COL3_G, COL3_P}},
     {{COL0_G, COL0_P}, {COL1_G, COL1_P}, {COL2_G, COL2_P}, {COL3_G, COL3_P}},
     {{COL0_G, COL0_P}, {COL1_G, COL1_P}, {COL2_G, COL2_P}},
     {{COL0_G, COL0_P}, {COL1_G, COL1_P}, {COL2_G, COL2_P}, {COL3_G, COL3_P}},
     {{COL0_G, COL0_P}, {COL1_G, COL1_P}}}};

/**
 * @name: Oreo097
 * @msg: 功能键的扫描逻辑表目前只使用一个键层所以只设置一个功能键
 * @param {type} 
 * @return {type} 
 */
kbd_logicmap_fkey_t kbd_logicmap_fkey = {
    1,
    {{0, 0}},
    {0}};

/**
 * @name: Oreo097
 * @msg: 键盘扫描相关设置
 * @param {type} 
 * @return {type} 
 */
kbd_scan_config_t kbd_scan_config = {
    1};

/**
 * @name: Oreo097
 * @msg: 防抖函数
 * @param {type} 
 * @return {type} 
 */
bool KBD_SCAN_RMJ_DELAY(uint8_t time,kbd_gpio_t gpio)
{
    KBD_DELAY(time);
    return pinRead(gpio);
}

/**
 * @name: Oreo097
 * @msg: 键层的数组
 * @param {type} 
 * @return {type} 
 */
 kbd_keymap_layer_t layer[4];
 kbd_keymap_layer_t * layer_ptr;//指向键层的指针

/**
 * @name: Oreo097
 * @msg: 扫描初始化函数,主要用于加载相关键层进入内存；
 * @param {type} 
 * @return {type} 
 */
void KBD_SCAN_INIT()
{
    layer_ptr=&layer;//指针指向相关数组
}

/**
 * @name: Oreo097
 * @msg: 扫描功能键（关于功能键，现在先写两种切换方式，一种是按住切换，一种是循环切换，目前打算做2个键层，所以只使用按下切换）
 * @param {kbd_gpio_map_t gpio_map,kbd_logicmap_fkey_t fkey_logic_map} 
 * @return {kbd_ans_fkey_t} 
 */
kbd_ans_fkey_t KBD_SCAN_SCAN_FKEY(kbd_gpio_map_t gpio_map, kbd_logicmap_fkey_t logic_map)
{
    kbd_ans_fkey_t fkey_ans;
    fkey_ans.index=0;
    for (int index = 0; index < logic_map.number; index++)
    {
        pinUp(gpio_map.gpio_row[logic_map.gpio_map[index][0]]);
        
        if(pinRead(gpio_map.gpio_col[logic_map.gpio_map[index][0]][logic_map.gpio_map[index][1]])==true)
        {
           if(KBD_SCAN_RMJ_DELAY(kbd_scan_config.rmj_time,gpio_map.gpio_col[logic_map.gpio_map[index][0]][logic_map.gpio_map[index][1]])==true)
           {
               fkey_ans.ans[fkey_ans.index]=logic_map.keyword[index];
               //fkey_ans.index++;
               break;
           }
        }
    }
    return fkey_ans;
}

/**
 * @name: Oreo097
 * @msg: 切换键层的程序，由于只使用按下切换
 * @param {type} 
 * @return {type} 
 */
void KBD_SCAN_SWITCH_LAYER(kbd_ans_fkey_t fkey_ans)
{
    if(fkey_ans.index>0)
    {
        
    }
}



/**
 * @name: Oreo097
 * @msg: 扫描特殊按键
 * @param {type} 
 * @return {type} 
 */
kbd