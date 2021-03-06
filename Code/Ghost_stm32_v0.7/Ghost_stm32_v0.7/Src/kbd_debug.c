/*
 * @Descripttion: 用来使用串口输出相关的信息的debug函数文件
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-10 15:56:31
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-08-02 09:13:07
 */
#include "kbd_debug.h"


/**
 * @name: Oreo097
 * @msg: 重定向printf函数，需要重写fputc函数
 * @param {} 
 * @return: int
 */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100);
    return 0;
}

/**
 * @name: Oreo097
 * @msg: 用来检测按键按下的函数，当按键按下去的时候会使用串口输出相关信息
 * @param {uint8_t 行，uint8_t 列，bool 状态} 
 * @return:void 
 */
void KBD_DBG_KEY(uint8_t row, uint8_t col, bool status)
{
    if (status == 1)
    {
        printf("%d,%d is pressed down\n", row, col);
    }
}

/**
 * @name: Oreo097
 * @msg: 输出扫描结果的DBG函数，用来输出扫描结果，仅限6KRO
 * @param {kbd_scan_ans_t * 答案名称} 
 * @return: void
 */
// void KBD_DBG_ANS_6KRO(kbd_scan_ans_t *ans)
// {
//     printf("%d keys ware pressed down\n", ans->index_akey);
//     printf("FKEY ANS:\n");
//     for (uint8_t index=0;index< ans->index_fkey; index++)
//     {
//         if (ans->array[index][0] == 0xff)
//         {
//             continue;
//         }
//         printf("%d,%d\n", ans->array[index][0], ans->array[index][1]);
//     }
//     printf("*FKEY END*\n");
// }

/**
 * @name: Oreo097
 * @msg: 用于通过串口输出输出防抖移除的按键
 * @param {(uint8_t 行，uint8_t 列} 
 * @return: void
 */
void KBD_DBG_RMJ(uint8_t row, uint8_t col)
{
    printf("%d,%d is removed\n", row, col);
}

/**
 * @name: Oreo097
 * @msg: 用于使用串口输出report的函数，仅限6KRO
 * @param {uint8_t * 报告}} 
 * @return: void
 */
void KBD_DBG_REP_6KRO(uint8_t *report)
{
    uint8_t map[] = "0,0,0,0,0,0,0,0\n";
    uint8_t end[] = "******over******\n";
    map[0] = *report;
    map[2] = *(++report);
    map[4] = *(++report);
    map[6] = *(++report);
    map[8] = *(++report);
    map[10] = *(++report);
    map[12] = *(++report);
    map[14] = *(++report);
    send(map);
    send(end);
}

/**
 * @name: Oreo097
 * @msg: 
 * @param {type} 
 * @return: 
 */
void KBD_DBG_SCAN_CALU_NUM(uint8_t row,uint8_t col)
{
    printf("%d ,%d key is still pressed\n",row,col);
}

/**
 * @name: Oreo097
 * @msg: 
 * @param {type} 
 * @return: 
 */
void KBD_DBG_SCAN_FKEY();
