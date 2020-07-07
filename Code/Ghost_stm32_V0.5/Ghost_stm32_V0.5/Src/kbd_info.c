/**
 * 本文件主要用于实现各种矩阵
 * 包括 物理上的GPIO矩阵--供扫描使用
 * 功能键、特殊键、普通键的矩阵
 * */




#include "kbd_info.h"


//物理按键的GPIO矩阵
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


//普通按键的键值矩阵
kbd_map_keyword_t kbd_map_keyword_akey[5][4] = {
    {Keypad_NumLock, Keypad_ChuHao, Keypad_ChengHao, Keypad_JianHao},
    {Keypad_7_and_Home, Keypad_8_and_UpArrow, Keypad_9_and_PageUp, Keypad_JiaHao},
    {Keypad_4_and_LeftArrow, Keypad_5, Keypad_6_and_RightArrow},
    {Keypad_1_and_End, Keypad_2_and_DownArrow, Keypad_3_and_PageDn, Keyboard_ENTER},
    {Keypad_0_and_Insert, Keypad_Dian_and_Delete},
};


//特殊键的键值矩阵，这里指的是在MAP_GPIO_PHY的位置
kbd_map_keyword_t kbd_map_keyword_skey[5][4] = {
    {0, 0, 0, 0},
    {0},
    {0},
    {0},
    {0}};


//功能键的键值矩阵
kbd_map_keyword_t kbd_map_keyword_fkey[5][4] = {
    {0},
    {0, 0, 0, 0},
    {0},
    {0},
    {0}};


//普通按键的位置矩阵
kbd_map_akey_t kbd_map_akey = {
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


//特殊按键的位置矩阵
kbd_map_fkey_t kbd_map_fkey = {
    NUM_FKEY,
    {{1, 3}}};

//特殊按键的位置矩阵
kbd_map_skey_t kbd_map_skey = {
    NUM_SKEY,
    {{0, 3}}

};
