/*
 * @Descripttion: 
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-08-02 09:33:05
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-08-02 10:00:07
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



