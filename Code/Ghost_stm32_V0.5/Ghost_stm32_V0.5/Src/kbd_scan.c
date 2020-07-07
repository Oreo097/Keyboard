/*
 * @Descripttion:键盘矩阵扫描的函数实现
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-07 17:39:38
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-07 23:50:03
 */

#include "kbd_scan.h"
#include "stdlib.h"

kbd_ans_t *ans;
kbd_ans_t kbd_ans;

// kbd_ans_t *ans_b;
// kbd_ans_t kbd_ans_backup;

uint8_t checkpoint_change = 0;

uint8_t kbd_sacn_other[6][2]; //这是用来存储扫描的其他按键的

extern kbd_map_gpio_t map_key_phy; //物理接盘的GPIO矩阵

extern kbd_map_akey_t kbd_map_akey; //普通按键的矩阵

extern kbd_map_fkey_t kbd_map_fkey; //功能按键的矩阵

extern kbd_map_skey_t kbd_map_skey; //特殊按键的矩阵

/**
 * @name: Oreo097
 * @msg: 如果上次结果小于6，全部扫描，如果上次结果为6则按键改变后才重新扫描
 * @param {type} 
 * @return: 
 */
void KBD_SCAN_MAIN(void)
{
    KBD_SCAN_ANS();
    if (checkpoint_change == 1)
    {
#if (NUM_AKEY != 0)
        KBD_SCAN_FKEY(); //扫描功能键
#endif
//HAL_Delay(100);
#if (NUM_SKEY != 0)
        KBD_SCAN_SKEY(); //扫描特殊键
#endif
//HAL_Delay(100);
#if (NUM_AKEY != 0)
        KBD_SCAN_AKEY(); //扫描普通键
#endif

        KBD_DELAY(1); //延迟1ms防抖

        KBD_SCAN_RMJ();
        //HAL_Delay(100);
        KBD_REPORT_MAKE();     //生成报告
        KBD_USB_SEND_REPORT(); //发送报告
    }
    //HAL_Delay(100);
}

// //初始化报表的函数，仅用于测试
// void test_free(void)
// {
//     uint8_t index;

//     for (index = 0; index <= ANS_NUM; index++)
//     {
//         ans->map[index][0] = 0xFF;
//         ans->map[index][1] = 0xFF;
//     }
//     ans->index_fkey = 0;
//     ans->index_akey = 0;
//     ans->index_skey = 0;
// }

//扫描结果初始化函数，仅用于程序初始化时
void KBD_SCAN_ANS_INIT(void)
{
    uint8_t index;
    ans = &kbd_ans;
#ifdef DBG_MODE
    printf("ans inited\n");
#endif
    for (index = 0; index <= ANS_NUM; index++)
    {
        ans->map[index][0] = 0xFF;
        ans->map[index][1] = 0xFF;
    }
    ans->index_fkey = 0;
    ans->index_akey = 0;
    ans->index_skey = 0;
}

//扫描结果过程中初始化函数，主要用于程序执行过程中的初始化
void KBD_SCAN_ANS_REINIT(void)
{
    uint8_t index;

    for (index = 0; index <= ans->index_akey; index++)
    {
        ans->map[index][0] = 0xFF;
        ans->map[index][1] = 0xFF;
    }
    ans->index_fkey = 0;
    ans->index_akey = 0;
    ans->index_skey = 0;
}

//键盘防抖函数，按键按下过程中并不是线性的，可能存在反复现象，所以需要防抖
void KBD_SCAN_RMJ(void)
{
    uint8_t checkpoint;
    uint8_t buffer_pin;
    if (ans->index_akey != 0)
    {
        for (checkpoint = 0; checkpoint < (ans->index_akey); checkpoint++)
        {
            buffer_pin = ans->map[checkpoint][0];
            pinUp(map_key_phy.gpio_row[buffer_pin]);
            if (pinRead(map_key_phy.gpio_col[ans->map[checkpoint][0]][ans->map[checkpoint][1]]) != 1)
            {
                ans->map[checkpoint][0] = ans->map[checkpoint][1] = 0xFF;
#ifdef DBG_MODE
                report_rm(ans->map[checkpoint][0], ans->map[checkpoint][1]);
#endif
            }
            pinDown(map_key_phy.gpio_row[buffer_pin]);
        }
    }
#ifdef DBG_MODE
    printf("rmjit complete\n");
#endif
}

//扫描功能按键的函数
#if (NUM_FKEY != 0)
void KBD_SCAN_FKEY(void)
{
    uint8_t index;
    //printf("scan fkey!\n");
    ans->index_fkey = 0;
    for (index = 0; index < kbd_map_fkey.num_key; index++)
    {
        pinUp(map_key_phy.gpio_row[kbd_map_fkey.key[index][0]]);
        if (pinRead(map_key_phy.gpio_col[kbd_map_fkey.key[index][0]][kbd_map_fkey.key[index][1]]) == 1)
        {
#ifdef DBG_MODE
            printf("fkey pressed down\n");
#endif
            ans->map_fkey[ans->index_fkey][0] = kbd_map_fkey.key[index][0];
            ans->map_fkey[ans->index_fkey][1] = kbd_map_fkey.key[index][1];
            ans->index_fkey++;
        }
        pinDown(map_key_phy.gpio_row[kbd_map_fkey.key[index][0]]);
    }
#ifdef DBG_MODE
    printf("scan fkey complete!\n");
#endif
}
#endif

//扫描特殊按键的函数
#if (NUM_SKEY != 0)
void KBD_SCAN_SKEY(void)
{
    uint8_t index;
    //printf("scan skey!\n");
    ans->index_skey = 0;
    for (index = 0; index < kbd_map_skey.num_key; index++)
    {
        pinUp(map_key_phy.gpio_row[kbd_map_skey.key[index][0]]);
        if (pinRead(map_key_phy.gpio_col[kbd_map_skey.key[index][0]][kbd_map_skey.key[index][1]]) == 1)
        {
#ifdef DBG_MODE
            printf("skey pressed down\n");
#endif
            ans->map_skey[ans->index_skey][0] = kbd_map_skey.key[index][0];
            ans->map_skey[ans->index_skey][1] = kbd_map_skey.key[index][1];
            ans->index_skey++;
        }
        pinDown(map_key_phy.gpio_row[kbd_map_skey.key[index][0]]);
    }
#ifdef DBG_MODE
    printf("scan skey complete!\n");
#endif
}
#endif

//扫描普通按键的函数
#if (NUM_AKEY != 0)
void KBD_SCAN_AKEY(void)
{
    uint8_t index_row;
    uint8_t index_col;
    //printf("scan akey!\n");
    ans->index_akey = 0;
    for (index_row = 0; index_row < ROW_MAX; index_row++)
    {
        //printf("scan row %d\n", index_row);
        pinUp(map_key_phy.gpio_row[index_row]);
        //printf("pinup\n");
        for (index_col = 0; index_col < kbd_map_akey.num_row[index_row]; index_col++)
        {
            //printf("%d\n",kbd_map_akey.key[index_row][index_col]);
            if (pinRead(map_key_phy.gpio_col[index_row][kbd_map_akey.key[index_row][index_col]]) == 1)
            {
                printf("%d,%d pressed down\n", index_row, index_col);
                ans->map_akey[ans->index_akey][0] = index_row;
                ans->map_akey[ans->index_akey][1] = index_col;
                ans->index_akey++;
            }
        }
        pinDown(map_key_phy.gpio_row[index_row]);
        //printf("pindown\n");
    }
    checkpoint_change = 0;
#ifdef DBG_MODE
    printf("scan akey complete!\n");
#endif
}
#endif

/**
 * 为什么要扫描上一次的扫描结果
 * 就是为了能够减少report次数
 * 在蓝牙或者2.4G环境下，发送report需要大量的电量，为了保证长续航时间必须减少发送次数
 * 当检测到按键并没有变化时将不会发送report
 * */
//扫描上一次扫描结果的函数
void KBD_SCAN_ANS(void)
{
    uint8_t index_ans_skey;
    for(index_ans=0;index_ans<)
}