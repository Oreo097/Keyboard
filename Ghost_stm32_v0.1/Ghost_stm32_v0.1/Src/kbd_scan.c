#include "kbd_scan.h"
#include "stdlib.h"

kbd_ans_t *ans;
kbd_ans_t kbd_ans;
extern kbd_map_gpio_t map_key_phy;

void KBD_ANS_INIT()
{

    //ans=(kbd_ans_t *)malloc(sizeof(kbd_ans_t));
    //return ans;
    ans = &kbd_ans;
    ans->map[0][0] = 0xFF;
    ans->map[0][1] = 0xFF;
}

void test()
{
    uint8_t index;
    index = NULL;
    ans->index = 6;
    for (index = 0; index < 6; index++)
    {
        ans->map[index][0] = 1;
        ans->map[index][1] = 2;
    }
}

void KBD_SCAN_MAIN()
{

    uint8_t row_now, col_now;
    //char size[]="row size is \n";
    //KBD_ANS_INIT();
    for (row_now = 0; row_now < ROW_MAX; row_now++)
    {
        // pinUp(map_key_phy.gpio_row[row_now].gpio_group, map_key_phy.gpio_row[row_now].gpio_pin);
        pinUp(map_key_phy.gpio_row[row_now]);
        //size[8]=itoc(sizeof(map_key_phy.gpio_col[row_now]));
        //HAL_UART_Transmit(&huart1,size,14,100);
        for (col_now = 0; col_now < map_key_phy.col_num[row_now]; col_now++)
        {
            // if (pinRead(map_key_phy.gpio_col[row_now][col_now].gpio_group, map_key_phy.gpio_col[row_now][col_now].gpio_pin) == 1)
            if (pinRead(map_key_phy.gpio_col[row_now][col_now]) == 1)
            {
                ans->map[ans->index][0] = row_now;
                ans->map[ans->index][1] = col_now;
                ans->index++;
                report_key(row_now, col_now, 1);
                //HAL_Delay(10);
            }
        }
        // pinDown(map_key_phy.gpio_row[row_now].gpio_group, map_key_phy.gpio_row[row_now].gpio_pin);
        pinDown(map_key_phy.gpio_row[row_now]);
        //HAL_UART_Transmit(&huart1,"next row\n",10,100);
    }
    //report_map(ans);
    //test_free();
    HAL_Delay(2);
    KBD_SCAN_RMJ();
}

//初始化报表的函数
void test_free()
{

    //ans=(kbd_ans_t *)malloc(sizeof(kbd_ans_t));
    //free(ans);
    uint8_t index;

    for (index = 0; index <= ans->index; index++)
    {
        ans->map[index][0] = 0xFF;
        ans->map[index][1] = 0xFF;
    }
    ans->index = 0;
    //return ans;
}

void KBD_SCAN_RMJ()
{
    uint8_t checkpoint;
    uint8_t buffer_pin;
    if (ans->index != 0)
    {
        for (checkpoint = 0; checkpoint < (ans->index); checkpoint++)
        {
            // pinUp(map_key_phy.gpio_row[ans->map[checkpoint][0]].gpio_group,map_key_phy.gpio_row[ans->map[checkpoint][0]].gpio_pin);
            buffer_pin = ans->map[checkpoint][0];
            pinUp(map_key_phy.gpio_row[buffer_pin]);
            // if(pinRead(map_key_phy.gpio_col[ans->map[checkpoint][0]][ans->map[checkpoint][1]].gpio_group,map_key_phy.gpio_col[ans->map[checkpoint][0]][ans->map[checkpoint][1]].gpio_pin)!=1)
            if (pinRead(map_key_phy.gpio_col[ans->map[checkpoint][0]][ans->map[checkpoint][1]]) != 1)
            {
                ans->map[checkpoint][0] = ans->map[checkpoint][1] = 0xFF;
                report_rm(ans->map[checkpoint][0], ans->map[checkpoint][1]);
            }
            pinDown(map_key_phy.gpio_row[buffer_pin]);
        }
    }
    report_map(ans);
    test_free();
}