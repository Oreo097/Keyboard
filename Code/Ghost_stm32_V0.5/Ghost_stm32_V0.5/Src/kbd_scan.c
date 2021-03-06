/*
 * @Descripttion:键盘矩阵扫描的函数实现
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-07 17:39:38
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-08 21:56:49
 */

#include "kbd_scan.h"
#include "stdlib.h"
#include <stdbool.h>

kbd_ans_t_6 *ans;
kbd_ans_t_6 kbd_ans;

// kbd_ans_t *ans_b;
// kbd_ans_t kbd_ans_backup;

uint8_t checkpoint_change_akey;

uint8_t ans_akey_index_index;
uint8_t ans_akey_index[NUM_AKEY] = {0, 1, 2, 3, 4, 5}; //akey的补位索引值

bool checkpoint_change_skey = false;
bool checkpoint_change_fkey = false;
uint8_t blank_akey; //这是空白键的数量

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

/**
 * @name: Oreo097
 * @msg: 扫描结果初始化函数，仅用于程序初始化时
 * @param {type} 
 * @return: void
 */
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
    checkpoint_change_akey = 0;
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

/**
 * @name: Oreo097
 * @msg: 键盘防抖函数，按键按下过程中并不是线性的，可能存在反复现象，所以需要防抖
 * @param {type} 
 * @return: void
 */
void KBD_SCAN_RMJ(void)
{
    uint8_t index;
    uint8_t buffer_pin;
    if (ans->index_akey != 0)
    {
        for (index = 0; index < (NUM_AKEY + NUM_FKEY + NUM_SKEY); index++)
        {
            if (ans->map[index][0] == 0xff)
            {
                continue;
            }
            buffer_pin = ans->map[index][0];
            pinUp(map_key_phy.gpio_row[buffer_pin]);
            if (pinRead(map_key_phy.gpio_col[ans->map[index][0]][ans->map[index][1]]) != true)
            {
                ans->map[index][0] = ans->map[index][1] = 0xFF;
#ifdef DBG_MODE
                report_rm(ans->map[index][0], ans->map[index][1]);
#endif
            }
            pinDown(map_key_phy.gpio_row[buffer_pin]);
        }
    }
#ifdef DBG_MODE
    printf("rmjit complete\n");
#endif
}

#if (NUM_FKEY != 0)
/**
 * @name: Oreo097
 * @msg:扫描功能按键的函数 
 * @param {type} 
 * @return: void
 */
void KBD_SCAN_FKEY(void)
{
    uint8_t index;
    //printf("scan fkey!\n");
    ans->index_fkey = 0; //初始化fkey的索引
    for (index = 0; index < NUM_FKEY; index++)
    {
        pinUp(map_key_phy.gpio_row[kbd_map_fkey.key[index][0]]);
        if (pinRead(map_key_phy.gpio_col[kbd_map_fkey.key[index][0]][kbd_map_fkey.key[index][1]]) == true)
        {
#ifdef DBG_MODE
            printf("fkey pressed down\n");
#endif
            ans->map[ans->index_fkey][0] = kbd_map_fkey.key[index][0];
            ans->map[ans->index_fkey][1] = kbd_map_fkey.key[index][1];
            ans->index_fkey++;
            if (idnex_fkey > NUM_FKEY) //超出范围跳出循环
            {
                break;
            }
        }
        pinDown(map_key_phy.gpio_row[kbd_map_fkey.key[index][0]]);
    }
#ifdef DBG_MODE
    printf("scan fkey complete!\n");
#endif
}
#endif

#if (NUM_SKEY != 0)
/**
 * @name: Oreo097
 * @msg: 扫描特殊按键的函数
 * @param {type} 
 * @return: void
 */
void KBD_SCAN_SKEY(void)
{
    uint8_t index;
    //printf("scan skey!\n");
    ans->index_skey = ans->index_fkey; //把fkey的索引值传递到skey的索引上
    for (index = 0; index < NUM_SKEY; index++)
    {
        pinUp(map_key_phy.gpio_row[kbd_map_skey.key[index][0]]);
        if (pinRead(map_key_phy.gpio_col[kbd_map_skey.key[index][0]][kbd_map_skey.key[index][1]]) == true)
        {
#ifdef DBG_MODE
            printf("skey pressed down\n");
#endif
            ans->map[ans->index_skey][0] = kbd_map_skey.key[index][0];
            ans->map[ans->index_skey][1] = kbd_map_skey.key[index][1];
            ans->index_skey++;
        }
        pinDown(map_key_phy.gpio_row[kbd_map_skey.key[index][0]]);
    }
#ifdef DBG_MODE
    printf("scan skey complete!\n");
#endif
}
#endif

/**
 * @name: Oreo097
 * @msg: 扫描普通按键的函数
 * @param {type} 
 * @return: void
 */
#if (NUM_AKEY != 0)
void KBD_SCAN_AKEY(void)
{
    uint8_t index_row;
    uint8_t index_col;
    //printf("scan akey!\n");
    ans->index_akey = ans->index_skey; //把skey的索引值传递到akey上
    ans_akey_index_index = 0;          //归零索引值
    for (index_row = 0; index_row < ROW_MAX; index_row++)
    {
        //printf("scan row %d\n", index_row);
        pinUp(map_key_phy.gpio_row[index_row]);
        //printf("pinup\n");
        for (index_col = 0; index_col < kbd_map_akey.num_row[index_row]; index_col++)
        {
            //printf("%d\n",kbd_map_akey.key[index_row][index_col]);
            if (pinRead(map_key_phy.gpio_col[index_row][kbd_map_akey.key[index_row][index_col]]) == true)
            {
#ifdef DBG_MODE
                printf("%d,%d pressed down\n", index_row, index_col);
#endif
                if (KBD_SCAN_CHECK(index_row, index_col) == false) //如果没在队列中
                {
                    if (checkpoint_change_akey == 0)
                    {
                        pinDown(map_key_phy.gpio_row[index_row]);
                        return；
                    }
                    ans->map[ans_akey_index[ans_akey_index_index]][0] = index_row;
                    ans->map[ans_akey_index[ans_akey_index_index]][1] = index_col;
                    checkpoint_change_akey--;
                }
                if (checkpoint_change_akey == 0)
                {
                    pinDown(map_key_phy.gpio_row[index_row]);
                    return；
                }
            }
        }
        pinDown(map_key_phy.gpio_row[index_row]);
        //printf("pindown\n");
    }
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
/**
 * @name: Oreo097
 * @msg: 检查上次扫描的答案
 * @param {type} 
 * @return: void 只改变全局变量checkpoint_change的值
 */
void KBD_SCAN_ANS(void)
{
#if (NUM_FKEY != 0)
    for (uint8_t index = 0; index < (ans->index_fkey); index++) //先检查fkey有没有变化
    {
        uint8_t buffer_pin = ans->map[index][0];
        pinUp(map_key_phy.gpio_row[buffer_pin]);
        if (pinRead(map_key_phy.gpio_col[ans->map[index][0]][ans->map[index][1]]) != true)
        {
            ans->map[index][0] = ans->map[index][1] = 0xFF; //清空ans的值
            checkpoint_change_fkey = true;
            pinDown(map_key_phy.gpio_row[buffer_pin]);
            break;
        }
        pinDown(map_key_phy.gpio_row[buffer_pin]);
    }
#endif
#if (NUM_SKEY != 0)
    for (uint8_t index = (ans->index_fkey); index < (ans->index_skey); index++) //检查skey
    {
        uint8_t buffer_pin = ans->map[index][0];
        pinUp(map_key_phy.gpio_row[buffer_pin]);
        if (pinRead(map_key_phy.gpio_col[ans->map[index][0]][ans->map[index][1]]) != true)
        {
            ans->map[index][0] = ans->map[index][1] = 0xFF; //清空ans的值
            checkpoint_change_skey = true;
            pinDown(map_key_phy.gpio_row[buffer_pin]);
            break;
        }
        pinDown(map_key_phy.gpio_row[buffer_pin]);
    }
#endif
#if (NUM_AKEY != 0)
    checkpoint_change_akey = 0;                                                            //初始化计数值
    ans_akey_index_index = 0;                                                              //归零索引值
    for (uint8_t index = (ans->index_skey); index < (ans->index_skey + NUM_AKEY); index++) //检查akey
    {
        if (ans->map[index][0] != 0xff)
        {
            uint8_t buffer_pin = ans->map[index][0];
            pinUp(map_key_phy.gpio_row[buffer_pin]);
            if (pinRead(map_key_phy.gpio_col[ans->map[index][0]][ans->map[index][1]]) != true)
            {
                ans->map[index][0] = ans->map[index][1] = 0xFF; //清空ans的值
                ans_akey_index[ans_akey_index_index] = index;   //储存索引位置
                ans_akey_index_index++;
                checkpoint_change_akey++;
            }
            pinDown(map_key_phy.gpio_row[buffer_pin]);
        }
        else
        {
            ans_akey_index[ans_akey_index_index] = index; //储存索引位置
            ans_akey_index_index++;
            checkpoint_change_akey++;
        }
    }
    ans_akey_index_index = 0;
#endif
}

/**
 * @name: Oreo097
 * @msg: 这是检查akey按键是否在ans队列中的函数
 * @param {type} 
 * @return: 如果在队列中返回true如果不在队列中或者队列为0直接返回false
 */
bool KBD_SCAN_CHECK(uint8_t row, uint8_t col)
{
    if ((ans->index_akey - ans->index_skey) == 0) //如果上次扫描的结果为0直接返回false
    {
        return false;
    }
    else
    {
        for (uint8_t index = ans->index_skey; index < ans->index_akey; index++)
        {
            if (row == (ans->map[index][0]))
            {
                if (col = (ans->map[index][1]))
                {
                    return true;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }
        return false;
    }
}
