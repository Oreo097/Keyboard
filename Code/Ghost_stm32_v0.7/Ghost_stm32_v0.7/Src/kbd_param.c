/*
 * @Descripttion: 这是用来实例化一些基础的变量，包括键盘矩阵物理上的GPIO表，扫描逻辑的表等
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-09 22:28:21
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-11 16:48:45
 */

#include "kbd_param.h"

/**
 * @name: Oreo097
 * @msg: 物理按键的矩阵，GPIO表
 * @param {type} 
 * @return: 
 */
kbd_map_gpio_t map_key_phy = {
    {{ROW0_G, ROW0_p}, {ROW1_G, ROW1_P}, {ROW2_G, ROW2_P}, {ROW3_G, ROW3_P}, {ROW4_G, ROW4_P}},
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
kbd_map_gpio_t *gpio_map = &map_key_phy;

#if (FKEY_MAX != 0)
/**
 * @name: Oreo097
 * @msg: 功能键（FKEY）的逻辑扫描表
 * @param {type} 
 * @return: 
 */
kbd_map_fkey_logic_t kbd_map_fkey = {
    {{1, 3}}};
kbd_map_fkey_logic_t *logicmap_fkey = &kbd_map_fkey;
#endif

#if (SKEY_MAX != 0)
/**
 * @name: Oreo097
 * @msg: 特殊按键（SKEY）的逻辑扫描表
 * @param {type} 
 * @return: 
 */
kbd_map_skey_logic_t kbd_map_skey = {
    {{0, 3}}};
kbd_map_skey_logic_t *logicmap_skey = &kbd_map_skey;
#endif

#if (AKEY_MAX != 0)
/**
 * @name: Oreo097
 * @msg:普通案件的逻辑扫描表 
 * @param {type} 
 * @return: 
 */
kbd_map_akey_logic_t kbd_map_akey = {
    {4,
     4,
     3,
     4,
     2},
    {{0, 1, 2, 3},
     {0, 1, 2, 3},
     {0, 1, 2},
     {0, 1, 2, 3},
     {0, 1}}};
kbd_map_akey_logic_t * logicmap_akey = &kbd_map_akey;

/**
 * @name: Oreo097
 * @msg: 按键的键值矩阵，用来供程序寻找对应的值
 * @param {type} 
 * @return: 
 */
kbd_map_keyword_t kbd_map_keyword_akey[ROW_MAX][COL_MAX] = {
    {Keypad_NumLock, Keypad_ChuHao, Keypad_ChengHao, Keypad_JianHao},
    {Keypad_7_and_Home, Keypad_8_and_UpArrow, Keypad_9_and_PageUp, Keypad_JiaHao},
    {Keypad_4_and_LeftArrow, Keypad_5, Keypad_6_and_RightArrow},
    {Keypad_1_and_End, Keypad_2_and_DownArrow, Keypad_3_and_PageDn, Keyboard_ENTER},
    {Keypad_0_and_Insert, Keypad_Dian_and_Delete},
};

#endif
