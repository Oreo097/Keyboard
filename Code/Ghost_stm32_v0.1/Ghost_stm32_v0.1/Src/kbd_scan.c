#include "kbd_scan.h"
#include "stdlib.h"

kbd_ans_t *ans;
kbd_ans_t kbd_ans;

uint8_t checkpoint_change = 0;

extern kbd_map_gpio_t map_key_phy;

extern kbd_map_akey_t kbd_map_akey;

extern kbd_map_fkey_t kbd_map_fkey;

extern kbd_map_skey_t kbd_map_skey;

void KBD_ANS_INIT(void)
{
    ans = &kbd_ans;
    ans->map[0][0] = 0xFF;
    ans->map[0][1] = 0xFF;
    printf("ans inited\n");
}

void KBD_SCAN_MAIN(void)
{
    KBD_SCAN_ANS();
    if (checkpoint_change == 1)
    {
        KBD_SCAN_FKEY();
        //HAL_Delay(100);
        KBD_SCAN_SKEY();
        //HAL_Delay(100);
        KBD_SCAN_AKEY();
        KBD_SCAN_RMJ();
        //HAL_Delay(100);
        KBD_REPORT_MAKE();
    }
    HAL_Delay(1000);
}

//初始化报表的函数
void test_free(void)
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
                report_rm(ans->map[checkpoint][0], ans->map[checkpoint][1]);
            }
            pinDown(map_key_phy.gpio_row[buffer_pin]);
        }
    }
    printf("rmjit complete\n");
}

void KBD_SCAN_FKEY(void)
{
    uint8_t index;
    printf("scan fkey!\n");
    ans->index_fkey = 0;
    for (index = 0; index < kbd_map_fkey.num_key; index++)
    {
        pinUp(map_key_phy.gpio_row[kbd_map_fkey.key[index][0]]);
        if (pinRead(map_key_phy.gpio_col[kbd_map_fkey.key[index][0]][kbd_map_fkey.key[index][1]]) == 1)
        {
            printf("fkey pressed down\n");
            ans->map[ans->index_fkey][0] = kbd_map_fkey.key[index][0];
            ans->map[ans->index_fkey][1] = kbd_map_fkey.key[index][1];
            ans->index_fkey++;
        }
        pinDown(map_key_phy.gpio_row[kbd_map_fkey.key[index][0]]);
    }
    printf("scan fkey complete!\n");
}

void KBD_SCAN_SKEY(void)
{
    uint8_t index;
    printf("scan skey!\n");
    kbd_ans.index_skey = kbd_ans.index_fkey;
    for (index = 0; index < kbd_map_skey.num_key; index++)
    {
        pinUp(map_key_phy.gpio_row[kbd_map_skey.key[index][0]]);
        if (pinRead(map_key_phy.gpio_col[kbd_map_skey.key[index][0]][kbd_map_skey.key[index][1]]) == 1)
        {
            printf("skey pressed down\n");
            ans->map[ans->index_skey][0] = kbd_map_skey.key[index][0];
            ans->map[ans->index_skey][1] = kbd_map_skey.key[index][1];
            ans->index_skey++;
        }
        pinDown(map_key_phy.gpio_row[kbd_map_skey.key[index][0]]);
    }
    printf("scan skey complete!\n");
}

void KBD_SCAN_AKEY(void)
{
    uint8_t index_row;
    uint8_t index_col;
    printf("scan akey!\n");
    ans->index_akey = ans->index_skey;
    for (index_row = 0; index_row < ROW_MAX; index_row++)
    {
        printf("scan row %d\n", index_row);
        pinUp(map_key_phy.gpio_row[index_row]);
        //printf("pinup\n");
        for (index_col = 0; index_col < kbd_map_akey.num_row[index_row]; index_col++)
        {
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
    printf("scan akey complete!\n");
}

void KBD_SCAN_ANS(void)
{
    uint8_t checkpoint;
    uint8_t buffer_pin;
    if (ans->index_akey == REPORT_MAX)
    {
        for (checkpoint = 0; checkpoint < (ans->index_akey); checkpoint++)
        {
            buffer_pin = ans->map[checkpoint][0];
            pinUp(map_key_phy.gpio_row[buffer_pin]);
            if (pinRead(map_key_phy.gpio_col[ans->map[checkpoint][0]][ans->map[checkpoint][1]]) != 1)
            {
                printf("ans changed\n");
                test_free();
                checkpoint_change = 1;
                break;
            }
            pinDown(map_key_phy.gpio_row[buffer_pin]);
            printf("keys not changed\n");
        }
    }
    else
    {
        printf("no ans\n");
        checkpoint_change = 1;
    }
    printf("scan ans complete\n");
}
