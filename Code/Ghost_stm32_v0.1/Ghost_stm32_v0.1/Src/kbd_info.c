#include "kbd_info.h"


kbd_map_gpio_t map_key_phy = {
    {{ROW0_G, ROW0_p}, {ROW1_G, ROW1_P}, {ROW2_G, ROW2_P}, {ROW3_G, ROW3_P}, {ROW4_G, ROW4_P}},
    {4,
     4,
     4,
     3,
     3},
    {{{COL0_G, COL0_P}, {COL1_G, COL1_P}, {COL2_G, COL2_P}, {COL3_G, COL3_P}},
     {{COL0_G, COL0_P}, {COL1_G, COL1_P}, {COL2_G, COL2_P}, {COL3_G, COL3_P}},
     {{COL0_G, COL0_P}, {COL1_G, COL1_P}, {COL2_G, COL2_P}, {COL3_G, COL3_P}},
     {{COL0_G, COL0_P}, {COL1_G, COL1_P}, {COL2_G, COL2_P}},
     {{COL0_G, COL0_P}, {COL1_G, COL1_P}, {COL3_G, COL3_P}}}};


kbd_map_keyword_t kbd_map_keyword[5][4]={
    {Keypad_NumLock,Keypad_ChuHao,Keypad_ChengHao,Keyboard_ESCAPE},
    {Keypad_7_and_Home,Keypad_8_and_UpArrow,Keypad_9_and_PageUp,Keypad_JianHao},
    {Keypad_4_and_LeftArrow,Keypad_5,Keypad_6_and_RightArrow,Keypad_JiaHao},
    {Keypad_1_and_End,Keypad_2_and_DownArrow,Keypad_3_and_PageDn},
    {Keypad_0_and_Insert,Keypad_Dian_and_Delete,Keyboard_ENTER},
};



kbd_map_akey_t kbd_map_akey={
    {
        3,
        3,
        4,
        3,
        3
    },
    {
        {0,1,2},
        {0,1,2},
        {0,1,2,3},
        {0,1,2},
        {0,1,3}
    }
};


kbd_map_fkey_t kbd_map_fkey={
    NUM_FKEY,
    {{1,3}}
};


kbd_map_skey_t kbd_map_skey={
    NUM_SKEY,
    {{0,3}}

};

