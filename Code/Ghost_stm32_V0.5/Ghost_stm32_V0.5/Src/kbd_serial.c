/*
 * @Descripttion: 这里存放的是串口DEBUG的函数实现
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-07 17:39:38
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-07 19:28:29
 */ 



#include "kbd_serial.h"

void report_map(kbd_ans_t *ans)
{
    uint8_t index;
    uint8_t words[] = " keys pressed totally\n";
    uint8_t map[] = " , \n";
    uint8_t end[] = "******over******\n";
    uint8_t fkey[]="  fkeys press down\n";
    uint8_t skey[]="  skeys press down\n";
    uint8_t akey[]="  akeys press down\n";
    words[0] = itoc(ans->index_akey);
    send(words);
    fkey[0]=(ans->index_fkey)+48;
    skey[0]=(ans->index_skey)+48;
    akey[0]=(ans->index_akey)+48;
    send(fkey);
    send(skey);
    send(akey);
    for (index = 0; index < ans->index_akey; index++)
    {
        map[0] = itoc(ans->map[index][0]);
        map[2] = itoc(ans->map[index][1]);
        send(map);
        HAL_Delay(30);
    }
    send(end);
}

uint8_t itoc(uint8_t num)
{
    return (num + 48);
}

void report_key(uint8_t row, uint8_t col, uint8_t status)
{
    uint8_t words[21] = " ,  is pressed down\n";
    if (status == 1)
    {
        words[0] = itoc(row);
        words[2] = itoc(col);
        send(words);
    }
}

void report_rm(uint8_t row, uint8_t col)
{
    uint8_t words[] = " ,  is removed\n";
    words[0] = itoc(row);
    words[2] = itoc(col);
    send(words);
}

int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 100);
    return 0;
}

void report_keyword(kbd_report_t *report)
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
    printf("%d,%d,%d,%d,%d,%d,%d,%d\n", map[0], map[2], map[4], map[6], map[8], map[10], map[12], map[14]);
    send(end);
}
