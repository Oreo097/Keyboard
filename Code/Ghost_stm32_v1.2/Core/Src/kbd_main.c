#include "kbd_main.h"
#include "kbd_scan.h"
#include "kbd_info.h"
#include "kbd_functions.h"

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
    {{0, 3}}};


uint8_t REPORT[6];//HID报文
kbd_ans_t_N ans;//扫描结果
