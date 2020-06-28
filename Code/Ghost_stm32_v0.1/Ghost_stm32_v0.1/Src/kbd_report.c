#include "kbd_report.h"

kbd_report_t kbd_report[REPORT_MAX];
extern kbd_map_keyword_t kbd_map_keyword[5][4];
extern kbd_ans_t* ans;//pointer for kbd_ans come form kbd_scan

void KBD_REPORT_MAKE(void)
{
    uint8_t index;
    for(index=0;index<(ans->index_akey);index++)
    {
        kbd_report[index]=kbd_map_keyword[ans->map[index][0]][ans->map[index][1]];
        if(index>=REPORT_MAX)
        {
            break;
        }
    }
    //test_free();
    report_keyword(kbd_report);
}



// void KBD_REPORT_MAKE(void)
// {
//     uint8_t index;
//     for()
// }




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
