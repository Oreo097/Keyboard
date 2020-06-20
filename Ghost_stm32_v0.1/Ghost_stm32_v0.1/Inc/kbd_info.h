#ifndef __KBD_INFO_H
#define __KBD_INFO_H


#ifndef __MAIN_H
#include "main.h"
#endif




#define ANS_NUM 128

#define ROW_MAX 5
#define COL_MAX 4

#define type_gpio GPIO_TypeDef


#define ROW0_G GPIOA
#define ROW0_p GPIO_PIN_0

#define ROW1_G GPIOA
#define ROW1_P GPIO_PIN_1

#define ROW2_G GPIOA
#define ROW2_P GPIO_PIN_2

#define ROW3_G GPIOA
#define ROW3_P GPIO_PIN_3


#define ROW4_G GPIOA
#define ROW4_P GPIO_PIN_4

#define COL0_G GPIOA
#define COL0_P GPIO_PIN_5

#define COL1_G GPIOA
#define COL1_P GPIO_PIN_6

#define COL2_G GPIOA
#define COL2_P GPIO_PIN_7

#define COL3_G GPIOB
#define COL3_P GPIO_PIN_0




typedef struct
{
    uint8_t index;
    uint8_t map[ANS_NUM][2];
}kbd_ans_t;


typedef struct 
{
    type_gpio* gpio_group;
    
    uint8_t gpio_pin;
}kbd_gpio_t;



typedef struct 
{
    kbd_gpio_t gpio_row[ROW_MAX];

    uint8_t col_num[ROW_MAX];
    
    kbd_gpio_t gpio_col[ROW_MAX][COL_MAX];

}kbd_map_gpio_t;





#endif
