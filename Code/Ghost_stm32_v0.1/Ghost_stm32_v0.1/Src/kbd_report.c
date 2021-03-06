#include "kbd_report.h"

kbd_report_t kbd_report[REPORT_MAX];
extern kbd_map_keyword_t kbd_map_keyword_akey[5][4];
extern kbd_map_keyword_t kbd_map_keyword_fkey[5][4];
extern kbd_map_keyword_t kbd_map_keyword_skey[5][4];
//extern kbd_ans_t kbd_ans;//pointer for kbd_ans come form kbd_scan
extern kbd_ans_t *ans;
void KBD_REPORT_MAKE(void)
{

    uint8_t index;
    uint8_t fkey = 0;
    //ans=&kbd_ans;
    report_map(ans);
    uint8_t index_report;

    for (index = 0; index < (ans->index_fkey); index++)
    {
        fkey |= kbd_map_keyword_fkey[ans->map[index][0]][ans->map[index][1]];
    }
    // switch (fkey)
    // {
    // case:

    // default:
    //     kbd_report[]0x00
    // }
    for (; index < (ans->index_skey); index++)
    {
        kbd_report[1] |= kbd_map_keyword_skey[ans->map[index][0]][ans->map[index][1]];
    }

    for (index_report = 2; index_report < REPORT_MAX; index_report++)
    {

        if (ans->map[index][0] == 0xFF)
        {
            break;
        }
        //printf("%d,%d\n",ans->map[index][0],ans->map[index][1]);
        kbd_report[index_report] = kbd_map_keyword_akey[ans->map[index][0]][ans->map[index][1]];
        index++;
        //printf("%d\n",kbd_report[index_report]);
    }
    report_keyword(kbd_report);
    KBD_REPORT_INIT();
}

void KBD_REPORT_SEND(void)
{
}

void KBD_REPORT_MAIN(void)
{
    KBD_REPORT_MAKE();

    KBD_REPORT_SEND();
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
}
