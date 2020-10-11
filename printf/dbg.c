/*
 * @Descripttion: 
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-10-11 10:18:56
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-10-11 15:02:10
 */
#include"dbg.h"
#include<stdio.h>


int fputc(int ch, FILE * stream)
{
    return ch;
}


int DBG_SEND(uint8_t * message)
{
    printf("DBG %s : %s\n",__func__,message);
    return 0;
}
