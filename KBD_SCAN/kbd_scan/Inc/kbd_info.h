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
    GPIO_TypeDef * gpio_group;
    //gpio 地址
    uint16_t * gpio_pin;
} gpio_t;

typedef struct
{
    //储存每行的列数
    uint8_t col_num[ROW_NUM];

    //这个是存放行GIPIO的数组
    gpio_t *keymap_phy_row;

    //这个是存放列GPIO的数组
    gpio_t *keymap_phy_col;
} keymap_phy_t;

//键盘扫描相关参数的结构体
typedef struct
{
    //扫描频率
    uint8_t freq_scan;

    //去抖时间
    uint8_t time_rmjit;

    //键盘物理层扫描反馈 使用16进制储存相关数据的话会节省点内存
    //uint8_t kbd_map_c1[COL_NUM];

    //写入map的指针
    uint8_t *map_write;

    //读取map的指针
    uint8_t *map_read;

    tim_info_t timer_scan;

    tim_info_t timer_rmjit;

    tim_info_t timer_repo;

    keymap_phy_t keymap_phy;

    uint8_t *keymap_1;

    uint8_t *keymap_2;

    uint8_t *keymap_3;

} kbd_info_t;


//扫描反馈值结构体
typedef struct 
{
    uint8_t answer_arry_num;
    //储存行数的数组
    uint8_t answer_row_arry[REPORT_MAX];
    //储存列数的数组
    uint8_t answer_col_arry[REPORT_MAX];

    gpio_t * answer_gpio_arry[REPORT_MAX];
    uint8_t answer_gpio_arry_num;

}answer_t;

#endif