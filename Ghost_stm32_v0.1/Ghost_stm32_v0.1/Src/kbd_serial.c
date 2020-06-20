#include "kbd_serial.h"




void report_map(kbd_ans_t *ans)
{
    uint8_t index;
    uint8_t words[] = " keys pressed totally\n";
    uint8_t map[] = " , \n";
    uint8_t end[] = "******over******\n";
    words[0] = itoc(ans->index);
    send(words);
    for (index = 0; index < ans->index; index++)
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
    //if(num<10)
    //{
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


int fputc(int ch,FILE *f)
{
    HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,100);
}