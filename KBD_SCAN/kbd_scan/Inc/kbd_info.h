/*
 * @Author: your name
 * @Date: 2020-06-04 20:55:03
 * @LastEditTime: 2020-06-06 17:50:13
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \kbd_scan\Inc\kbd_info.h
 */
#ifndef __KBD_INFO_H
#define __KBD_INFO_H

#ifndef __MAIN_H
#include "main.h"
#endif

//键盘行数列数等相关参数,注意要比实际行数少一行
#define ROW_NUM 5 //行数
#define COL_NUM 4 //列数

#define SPEC_NUM 8//特殊键个数

//层数
#define KEYMAP_NUM 3

//最大报告数
#define REPORT_MAX 6

typedef struct
{
    //计时器预分频
    uint32_t prescaler;
    //计时器溢出值
    uint32_t period;
} tim_info_t;

typedef struct
{
    //gpio 组地址
    GPIO_TypeDef *gpio_group;
    //gpio 地址
    uint16_t *gpio_pin;
} gpio_t;

typedef struct
{
    //这个是存放行GIPIO的数组
    gpio_t keymap_phy_row[ROW_NUM];
    //行索引
    uint8_t keymap_phy_row_index;

    //这个是存放列GPIO的数组
    gpio_t keymap_phy_col[ROW_NUM][COL_NUM];
    //列索引
    uint8_t keymap_phy_col_index;
    //储存每行的列数
    uint8_t col_num[ROW_NUM];
} keymap_phy_t;

//键盘扫描相关参数的结构体
typedef struct
{
    // //扫描频率
    // uint8_t freq_scan;

    // //去抖时间
    // uint8_t time_rmjit;

    //键盘物理层扫描反馈 使用16进制储存相关数据的话会节省点内存
    //uint8_t kbd_map_c1[COL_NUM];

    // //写入map的指针
    // uint8_t *map_write;

    // //读取map的指针
    // uint8_t *map_read;

    tim_info_t timer_scan;

    tim_info_t timer_rmjit;

    tim_info_t timer_repo;

    //物理键位
    keymap_phy_t keymap_phy;

    gpio_t keymap_phy_fn;

    gpio_t keymap_phy_spec[SPEC_NUM];

    uint8_t keymap_arry[KEYMAP_NUM][ROW_NUM][COL_NUM];

} kbd_info_t;

//扫描反馈值结构体
typedef struct
{
    uint8_t key_fn;

    //uint8_t key_spec[SPEC_NUM];

    uint8_t answer_arry_num;
    //储存行数的数组
    uint8_t answer_row_arry[REPORT_MAX];
    //储存列数的数组
    uint8_t answer_col_arry[REPORT_MAX];

    gpio_t * answer_gpio_arry[REPORT_MAX];
    uint8_t answer_gpio_arry_num;

} answer_t;

#endif