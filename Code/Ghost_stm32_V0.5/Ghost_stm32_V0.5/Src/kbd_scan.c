/*
 * @Descripttion: 
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-07 17:39:38
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-07 19:28:24
 */ 
/**
 * 本文件主要用于实现键盘矩阵的扫描
 * */

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

//扫描过程主函数
void KBD_SCAN_MAIN(void)
{
    KBD_SCAN_ANS();
    if (checkpoint_change == 1)
    {
        KBD_SCAN_FKEY(); //扫描功能键
        //HAL_Delay(100);
        KBD_SCAN_SKEY(); //扫描特殊键
        //HAL_Delay(100);
        KBD_SCAN_AKEY(); //扫描普通键
        KBD_SCAN_RMJ();
        //HAL_Delay(100);
        KBD_REPORT_MAKE();     //生成报告
        KBD_USB_SEND_REPORT(); //发送报告
    }
    //HAL_Delay(100);
}

//初始化报表的函数，仅用于测试
void test_free(void)
{
    uint8_t index;

    for (index = 0; index <= ANS_NUM; index++)
    {
        ans->map[index][0] = 0xFF;
        ans->map[index][1] = 0xFF;
    }
    ans->index_fkey = 0;
    ans->index_akey = 0;
    ans->index_skey = 0;
}

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
            ans->map[ans->index_fkey][0] = kbd_map_fkey.key[index][0];
            ans->map[ans->index_fkey][1] = kbd_map_fkey.key[index][1];
            ans->index_fkey++;
        }
        pinDown(map_key_phy.gpio_row[kbd_map_fkey.key[index][0]]);
    }
#ifdef DBG_MODE
    printf("scan fkey complete!\n");
#endif
}

//扫描特殊按键的函数
void KBD_SCAN_SKEY(void)
{
    uint8_t index;
    //printf("scan skey!\n");
    kbd_ans.index_skey = kbd_ans.index_fkey;
    for (index = 0; index < kbd_map_skey.num_key; index++)
    {
        pinUp(map_key_phy.gpio_row[kbd_map_skey.key[index][0]]);
        if (pinRead(map_key_phy.gpio_col[kbd_map_skey.key[index][0]][kbd_map_skey.key[index][1]]) == 1)
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

//扫描普通按键的函数
void KBD_SCAN_AKEY(void)
{
    uint8_t index_row;
    uint8_t index_col;
    //printf("scan akey!\n");
    ans->index_akey = ans->index_skey;
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
                ans->map[ans->index_akey][0] = index_row;
                ans->map[ans->index_akey][1] = index_col;
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

/**
 * 为什么要扫描上一次的扫描结果
 * 就是为了能够减少report次数
 * 在蓝牙或者2.4G环境下，发送report需要大量的电量，为了保证长续航时间必须减少发送次数
 * 当检测到按键并没有变化时将不会发送report
 * */
//扫描上一次扫描结果的函数
void KBD_SCAN_ANS(void)
{
    uint8_t checkpoint;
    uint8_t buffer_pin;

    if (ans->index_akey != 0) //检测扫描结果是否为空
    {
        if (((ans->index_akey) - (ans->index_skey)) == (REPORT_MAX - 2)) //检测报表是否写满
        {
            for (checkpoint = 0; checkpoint < 8; checkpoint++) //循环检测每个按键
            {
                buffer_pin = ans->map[checkpoint][0];
                pinUp(map_key_phy.gpio_row[ans->map[checkpoint][0]]);
                if (pinRead(map_key_phy.gpio_col[ans->map[checkpoint][0]][ans->map[checkpoint][1]]) != 1)
                {
#ifdef DBG_MODE
                    printf("ans changed\n");
#endif
                    KBD_SCAN_ANS_REINIT();
                    checkpoint_change = 1; //触发扳机
                    pinDown(map_key_phy.gpio_row[buffer_pin]);
                    break;
                }
                pinDown(map_key_phy.gpio_row[buffer_pin]);
            }
        }
        else
        {
#ifdef DBG_MODE
            printf("ans not enough\n");
#endif
            checkpoint_change = 1;
            KBD_SCAN_ANS_REINIT();
        }
    }
    else
    {
#ifdef DBG_MODE
        printf("no ans\n");
#endif
        checkpoint_change = 1;
    }
#ifdef DBG_MODE
    printf("scan ans complete\n");
#endif
}

// void KBD_SCAN_ANS(void)
// {
//     uint8_t numnber;    //这是用来计算需要新添加多少个值的按键
//     uint8_t buffer_pin; //用来暂存按键bufferpin，用于debug
//     uint8_t checkpoint; //用来计数的变量

//     uint8_t number = 0; //初始化number
//     //先检测上次是否有答案
//     if (ans->index_akey != 0)
//     {
//         //再检测按键是否大于6个
//         if (ans->index_akey >= 6)
//         {
//             //循环检测按键是否改变
//             for (checkpoint = 0; checkpoint < 6; checkpoint++) //这里先检测6个akey按键
//             {
//                 buffer_pin = ans->map[checkpoint][0]; //我觉得这句必要时可以注释掉
//                 pinUp(map_key_phy.gpio_row[ans->map[checkpoint][0]]);
//                 if (pinRead(map_key_phy.gpio_col[ans->map[checkpoint][0]][ans->map[checkpoint][1]]) != 1)
//                 {
//                     printf("6 ans changed\n");
//                     ans->map[checkpoint][0] = ans->map[checkpoint][1] = 0xFF; //去掉相应按键
//                     checkpoint_change = 1;                                    //触发扳机需要重现扫描按键
//                     number++;                                                 //这6个键中每检测到一个按键就number自加1

//                     //break;//如果在这里break会导致row被拉高后不再拉低
//                 }
//                 pinDown(map_key_phy.gpio_row[buffer_pin]);
//             }
//             for (; checkpoint < (ans->index_akey - 6-ans->index_skey); checkpoint++) //检测其他的按键，如果存在抬起的情况把ans消除
//             {
//                 pinUp(map_key_phy.gpio_row[ans->map[checkpoint][0]]);
//                 if (pinRead(map_key_phy.gpio_col[ans->map[checkpoint][0]][ans->map[checkpoint][1]]) != 1)
//                 {
//                     printf("other akey ans changed\n");
//                     ans->map[checkpoint][0] = ans->map[checkpoint][1] = 0xFF; //去掉相应按键
//                     //break;//如果在这里break会导致row被拉高后不再拉低
//                 }
//                 pinDown(map_key_phy.gpio_row[buffer_pin]);
//             }
//             //接下来是重点，扫描其他的按键
//         }
//     }
// }

// /**
//  * 扫描其他的按键
//  * */
// void KBD_SCAN_OTHER(uint8_t number)//参数是需要扫描按键的个数
// {
//     uint8_t index_row;
//     uint8_t index_col;
//     uint8_t index_ans;
//     ans->index_akey = ans->index_skey;
//     for (index_row = 0; index_row < ROW_MAX; index_row++) //循环扫描行
//     {
//         pinUp(map_key_phy.gpio_row[index_row]);
//         for (index_col = 0; index_col < kbd_map_akey.num_row[index_row]; index_col++) //循环扫描列
//         {
//             for(index_ans=0;index_ans<(ans->index_akey-ans->index_skey);index_ans++)//循环检测是否是ans中的按键
//             {
//                 if(index_row==ans->map[index_ans][0]&&index_col==ans->map[index_ans][1])//判断是否为ans的按键
//                 {
//                     continue;//跳过本次循环
//                 }
//             }
//             if (pinRead(map_key_phy.gpio_col[index_row][kbd_map_akey.key[index_row][index_col]]) == 1)
//             {
//                 printf("%d,%d pressed down\n", index_row, index_col);
//                 ans->map[ans->index_akey][0] = index_row;
//                 ans->map[ans->index_akey][1] = index_col;
//                 ans->index_akey++;
//             }
//         }
//         pinDown(map_key_phy.gpio_row[index_row]);
//     }
//     checkpoint_change = 0;
//     printf("scan akey complete!\n");
// }
