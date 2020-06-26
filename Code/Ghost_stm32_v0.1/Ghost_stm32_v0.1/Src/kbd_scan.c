#include "kbd_scan.h"
#include "stdlib.h"

kbd_ans_t *ans;
kbd_ans_t kbd_ans;
extern kbd_map_gpio_t map_key_phy;

extern kbd_map_akey_t kbd_map_akey;

extern kbd_map_fkey_t kbd_map_fkey;

extern kbd_map_skey_t kbd_map_skey;

void KBD_ANS_INIT(void)
{

    //ans=(kbd_ans_t *)malloc(sizeof(kbd_ans_t));
    //return ans;
    ans = &kbd_ans;
    ans->map[0][0] = 0xFF;
    ans->map[0][1] = 0xFF;
    printf("ans inited\n");
}

// void test(void)
// {
//     uint8_t index;
//     index = NULL;
//     ans->index = 6;
//     for (index = 0; index < 6; index++)
//     {
//         ans->map[index][0] = 1;
//         ans->map[index][1] = 2;
//     }
// }

// void KBD_SCAN_MAIN(void)
// {

//     uint8_t row_now, col_now;
//     //char size[]="row size is \n";
//     KBD_ANS_INIT();
//     for (row_now = 0; row_now < ROW_MAX; row_now++)
//     {
//         // pinUp(map_key_phy.gpio_row[row_now].gpio_group, map_key_phy.gpio_row[row_now].gpio_pin);
//         printf("row is %d\n", row_now);
//         pinUp(map_key_phy.gpio_row[row_now]);
//         //size[8]=itoc(sizeof(map_key_phy.gpio_col[row_now]));
//         //HAL_UART_Transmit(&huart1,size,14,100);
//         for (col_now = 0; col_now < map_key_phy.col_num[row_now]; col_now++)
//         {
//             // if (pinRead(map_key_phy.gpio_col[row_now][col_now].gpio_group, map_key_phy.gpio_col[row_now][col_now].gpio_pin) == 1)
//             if (pinRead(map_key_phy.gpio_col[row_now][col_now]) == 1)
//             {
//                 ans->map[ans->index][0] = row_now;
//                 ans->map[ans->index][1] = col_now;
//                 ans->index++;
//                 report_key(row_now, col_now, 1);
//                 //HAL_Delay(10);
//             }
//         }
//         // pinDown(map_key_phy.gpio_row[row_now].gpio_group, map_key_phy.gpio_row[row_now].gpio_pin);
//         pinDown(map_key_phy.gpio_row[row_now]);
//         //HAL_UART_Transmit(&huart1,"next row\n",10,100);
//     }
//     //report_map(ans);
//     //test_free();
//     HAL_Delay(2);
//     KBD_SCAN_RMJ();
// }

void KBD_SCAN_MAIN(void)
{
    KBD_SCAN_FKEY();
    KBD_SCAN_SKEY();
    KBD_SCAN_AKEY();
    KBD_SCAN_RMJ();
    KBD_REPORT_MAKE();
}





//初始化报表的函数
void test_free(void)
{

    //ans=(kbd_ans_t *)malloc(sizeof(kbd_ans_t));
    //free(ans);
    uint8_t index;

    for (index = 0; index <= ans->index_akey; index++)
    {
        ans->map[index][0] = 0xFF;
        ans->map[index][1] = 0xFF;
    }
    ans->index_fkey = 0;
    ans->index_akey=0;
    ans->index_skey=0;
    //return ans;
}

void KBD_SCAN_RMJ(void)
{
    uint8_t checkpoint;
    uint8_t buffer_pin;
    if (ans->index_akey != 0)
    {
        for (checkpoint = 0; checkpoint < (ans->index_akey); checkpoint++)
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
    //test_free();
    //printf("make report\n");
    
}


void KBD_SCAN_FKEY(void)
{
    uint8_t index;
    printf("scan fkey!\n");
    ans->index_fkey=0;
    for(index=0;index<=kbd_map_fkey.num_key;index++)
    {
        pinUp(map_key_phy.gpio_row[kbd_map_fkey.key[index][0]]);
        if(pinRead(map_key_phy.gpio_col[kbd_map_fkey.key[index][0]][kbd_map_fkey.key[index][1]])==1)
        {
            ans->map[ans->index_fkey][0] = kbd_map_fkey.key[index][0];
            ans->map[ans->index_fkey][1] = kbd_map_fkey.key[index][1];
            ans->index_fkey++;
        }
        pinDown(map_key_phy.gpio_row[kbd_map_fkey.key[index][0]]);
    }
    printf("scan over!\n");
}


void KBD_SCAN_SKEY()
{
    uint8_t index;
    printf("scan skey!\n");
    kbd_ans.index_skey=kbd_ans.index_fkey;
    for(index=0;index<=kbd_map_skey.num_key;index++)
    {
        pinUp(map_key_phy.gpio_row[kbd_map_skey.key[index][0]]);
        if(pinRead(map_key_phy.gpio_col[kbd_map_skey.key[index][0]][kbd_map_skey.key[index][1]])==1)
        {
            ans->map[ans->index_skey][0] = kbd_map_skey.key[index][0];
            ans->map[ans->index_skey][1] = kbd_map_skey.key[index][1];
            ans->index_skey++;
        }
        pinDown(map_key_phy.gpio_row[kbd_map_skey.key[index][0]]);
    }
    printf("scan over!\n");
}

void KBD_SCAN_AKEY()
{
    uint8_t index_row;
    uint8_t index_col;
    printf("scan akey!\n");
    ans->index_akey = ans->index_skey;
    for (index_row = 0; index_row <= NUM_FKEY; index_row++)
    {
        pinUp(map_key_phy.gpio_row[index_row]);
        for (index_col = 0; index_col <= kbd_map_akey.num_row[index_row]; index_col++)
        {
            if (pinRead(map_key_phy.gpio_col[index_row][kbd_map_akey.key[index_row][index_col]]) == 1)
            {
                ans->map[ans->index_akey][0] = index_row;
                ans->map[ans->index_akey][1] = index_col;
                ans->index_akey++;
            }
        }
        pinDown(map_key_phy.gpio_row[kbd_map_skey.key[index_row][0]]);
    }
    printf("scan over!\n");
}
