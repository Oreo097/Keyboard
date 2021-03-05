#ifndef __KBD_SCAN_H__
#define __KBD_SCAN_H__

#include "kbd_info.h"

//GPIO表
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

#define ANS_NUM 128

#define REPORT_MAX 6

#define ROW_MAX 5
#define COL_MAX 4

#define NUM_FKEY 1
#define NUM_SKEY 1
#define NUM_AKEY 104

#define type_gpio GPIO_TypeDef

typedef struct
{
    kbd_gpio_t gpio_row[ROW_MAX];

    uint8_t col_num[ROW_MAX];

    kbd_gpio_t gpio_col[ROW_MAX][COL_MAX];

} kbd_map_gpio_t;

typedef struct
{
    uint8_t num_row;
    uint8_t num_col[ROW_MAX];
    uint8_t key[ROW_MAX][COL_MAX];

} kbd_map_akey_t;

typedef struct
{
    uint8_t num_key;
    uint8_t key[NUM_FKEY][2];

} kbd_map_fkey_t;

typedef struct
{
    uint8_t num_key;
    uint8_t key[NUM_SKEY][2];

} kbd_map_skey_t;

typedef struct
{
    //当checkpoint为1的时候说明有未处理变动
    uint8_t index_fkey;
    // uint8_t checkpoint_fkey;
    uint8_t fkey_ans[NUM_FKEY][2];

    uint8_t index_skey;
    // uint8_t checkpoint_skey;
    uint8_t skey_ans[NUM_SKEY][2];

    uint8_t index_akey;//储存数组末尾位置
    // uint8_t checkpoint_akey;//储存是否有值的改变
    // uint8_t* index_akey_empty;//索引指针
    // uint8_t akey_empty[NUM_AKEY];//储存缺省值位置
    uint8_t akey_ans[NUM_AKEY][2];

} kbd_ans_t_N;

#endif