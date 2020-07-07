/*
 * @Descripttion: 有关报告生成的函数全在这里，本文件中的函数主要用于解析扫描结果和生成报告
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-07 17:39:38
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-07 22:06:42
 */

#include "kbd_report.h"
#include "kbd_usb.h"

extern kbd_map_keyword_t kbd_map_keyword_akey[5][4];
extern kbd_map_keyword_t kbd_map_keyword_fkey[5][4];
extern kbd_map_keyword_t kbd_map_keyword_skey[5][4];
//extern kbd_ans_t kbd_ans;//pointer for kbd_ans come form kbd_scan
extern kbd_ans_t *ans;

// kbd_ans_t *ans_b;
// kbd_ans_t kbd_ans_backup;

kbd_report_t kbd_report[REPORT_MAX];

//生成报告的函数，用来从kbd_ans中解析出键值并生成报告
void KBD_REPORT_MAKE(void)
{

    uint8_t index;
    uint8_t fkey = 0;
//ans=&kbd_ans;
#ifdef DBG_MODE
    report_map(ans);
#endif
    uint8_t index_report;

    for (index = 0; index < (ans->index_fkey); index++)
    {
        fkey |= kbd_map_keyword_fkey[ans->map[index][0]][ans->map[index][1]];
    }

    for (; index < (ans->index_skey); index++)
    {
        kbd_report[1] |= kbd_map_keyword_skey[ans->map[index][0]][ans->map[index][1]];
    }

    for (index_report = 2; index_report < REPORT_MAX; index_report++)
    {
        if (index_report - 2 >= (ans->index_akey - ans->index_skey))
        {
            break;
        }
        if (ans->map[index][0] == 0xFF)
        {
            break;
        }
        kbd_report[index_report] = kbd_map_keyword_akey[ans->map[index][0]][ans->map[index][1]];
        index++;
    }
#ifdef DBG_MODE
    report_keyword(kbd_report);
#endif
    //KBD_REPORT_INIT();
    //report_keyword(kbd_report);
}

void KBD_REPORT_MAIN(void)
{
    //KBD_REPORT_MAKE();

    //KBD_REPORT_SEND();
}

void KBD_REPORT_SELECT(void)
{
}

void KBD_REPORT_INIT(void)
{
    uint8_t index_report;
    for (index_report = 0; index_report <= REPORT_MAX; index_report++)
    {
        kbd_report[index_report] = 0;
    }
#ifdef DBG_MODE
    printf("init complete\n");
#endif
}
