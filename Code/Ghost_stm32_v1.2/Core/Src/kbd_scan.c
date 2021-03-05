#include "kbd_scan.h"
#include "kbd_info.h"
#include "kbd_functions.h"

//扫描键盘的函数
//扫描过程如下，先扫描功能键，再扫描特殊键，再扫描普通按键，特殊键和功能键，会导致开关开启和关闭，导致输出结果不同

//初始化扫描结果
void KBD_SCAN_INIT()
{
    ans.index_fkey = 0;
    ans.checkpoint_fkey = 0;
    ans.index_skey = 0;
    ans.checkpoint_skey = 0;
    ans.index_akey = 0;
    ans.index_akey_empty = ans.akey_ans[0][0];
}

//小循环初始化
void KBD_SCAN_REINIT(kbd_ans_t_N ans)
{
    for (uint8_t i = 0; i < NUM_AKEY; i++)
    {
        ans.akey_empty[i] = 0;
    }
    ans.index_akey_empty = ans.akey_ans[0][0];
}

//扫描功能键
void KBD_SCAN_FKEY(kbd_map_fkey_t fkey, kbd_map_gpio_t map_key_phy, kbd_ans_t_N ans)
{
    for (uint8_t i = 0; i <= fkey.num_key; i++)
    {
        KBD_GPIO_UP(map_key_phy.gpio_row[fkey.key[i][0]]);
        if (KBD_GPIO_READ(map_key_phy.gpio_col[fkey.key[i][0]][fkey.key[i][1]]) == 1)
        {
            ans.fkey_ans[ans.index_fkey][0] = fkey.key[i][0];
            ans.fkey_ans[ans.index_fkey][1] = fkey.key[i][1];
            ans.index_fkey++;
        }
        KBD_GPIO_DOWN(map_key_phy.gpio_row[fkey.key[i][0]]);
    }
}

//扫描特殊按键
void KBD_SACN_SKEY(kbd_map_skey_t skey, kbd_map_gpio_t map_key_phy, kbd_ans_t_N ans)
{
    for (uint8_t i = 0; i <= skey.num_key; i++)
    {
        KBD_GPIO_UP(map_key_phy.gpio_row[skey.key[i][0]]);
        if (KBD_GPIO_READ(map_key_phy.gpio_col[skey.key[i][0]][skey.key[i][1]]) == 1)
        {
            ans.fkey_ans[ans.index_skey][0] = skey.key[i][0];
            ans.fkey_ans[ans.index_skey][1] = skey.key[i][1];
            ans.index_fkey++;
        }
        KBD_GPIO_DOWN(map_key_phy.gpio_row[skey.key[i][0]]);
    }
}

//扫描普通按键
void KBD_SCAN_AKEY(kbd_map_akey_t akey, kbd_map_gpio_t map_key_phy, kbd_ans_t_N ans)
{
    for(uint8_t i=0;i<=akey.num_row;i++)
    {
        uint8_t row=akey.
        KBD_GPIO_UP(map_key_phy.gpio_row[row]);//拉高行
        for(uint8_t t=0;t<=akey.num_col[i];t++)
        {
            if(KBD_GPIO_READ(map_key_phy.gpio_col[i][t]))
            {
                ans.akey_ans[ans.index_akey][0]=i;
                ans.akey_ans[ans.index_akey][1]=t;
                ans.index_akey++;
            }
        }
        KBD_GPIO_DOWN(map_key_phy.gpio_row[i]);//拉低行

    }
}

// //第二次扫描按键
// void KBD_SCAN_CHECK(kbd_ans_t_N ans)
// {
//     // if ((ans.index_fkey + ans.index_skey + ans.index_akey) != 0) //判断上次是不是结果为空
//     // {
//     //     if (ans.index_fkey != 0)
//     //     {
//     //         for (uint8_t i = 0; i <= NUM_FKEY; i++) //扫描上次结果的功能键
//     //         {
//     //             uint8_t status = KBD_SCAN_SIMPKEY(ans.fkey_ans[i][0], ans.fkey_ans[i][1]);
//     //             if (status != 0)
//     //             {
//     //                 ans.checkpoint_fkey = 1;
//     //                 break;//一个功能键改变就会改变整个键值计算所以跳出循环
//     //             }
//     //         }
//     //     }
//     //     if(ans.index_skey!=0)
//     //     {
//     //         for(uint8_t i=0;i<=NUM_SKEY;i++)
//     //         {
//     //             uint8_t status=KBD_SCAN_SIMPKEY(ans.skey_ans[i][0],ans.skey_ans[i][1]);
//     //             if(status!=0)
//     //             {
//     //                 ans.checkpoint_skey=1;
//     //                 break;//一个特殊按键改变就会改变头两个键值，所以跳出循环
//     //             }
//     //         }
//     //     }

//     //没有必要检测那么多按键，直接再处理一次就好了
//     //只检测上次检测的按键
//         if(ans.index_akey!=0)
//         {
//             for(uint8_t i=0;i<=NUM_AKEY;i++)
//             {
//                 uint8_t status=KBD_SCAN_SIMPKEY(ans.akey_ans[i][0],ans.akey_ans[i][1]);
//                 if(status!=0)
//                 {
//                     ans.akey_ans[i][0]=ans.akey_ans[i][1]=0;//把所有值归零
//                     *ans.index_akey_empty=i;//把位置的值记录进去
//                     ans.checkpoint_akey++;//计算有几个键值改变了
//                 }
//             }
//         }
//     }
// }

//报文令使用文件处理
// //处理报文
// void KBD_SCAN_PROC()
// {
// }

// //寻找相同报文
// void KBD_SCAN_SEARCH()
// {
// }

// //替换报文
// void KBD_SCAN_REPLACE()
// {
// }

//扫描单个按键
uint8_t KBD_SCAN_SIMPKEY(uint8_t row, uint8_t col, kbd_map_gpio_t map_key_phy)
{
    uint8_t status = 0;
    KBD_GPIO_UP(map_key_phy.gpio_row[row]);
    status = KBD_GPIO_READ(map_key_phy.gpio_col[row][col]);
    KBD_GPIO_DOWN(map_key_phy.gpio_row[row]);
    return status;
}