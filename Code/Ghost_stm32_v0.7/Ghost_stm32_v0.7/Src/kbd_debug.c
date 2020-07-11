/*
 * @Descripttion: 用来使用串口输出相关的信息的debug函数文件
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-10 15:56:31
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-11 09:25:01
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
void KBD_DBG_KEY(uint8_t row,uint8_t col,bool status)
{
    uint8_t words[21] = " ,  is pressed down\n";
    if (status == 1)
    {
        words[0] = itoc(row);
        words[2] = itoc(col);
        send(words);
    }
}

/**
 * @name: Oreo097
 * @msg: 输出扫描结果的DBG函数，用来输出扫描结果
 * @param {kbd_scan_ans_t 答案名称} 
 * @return: void
 */
void KBD_DBG_ANS()
{
    
}