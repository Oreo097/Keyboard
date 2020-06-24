#include "kbd_report.h"

kbd_report_t kbd_report[REPORT_MAX];
kbd_report_t* report;
extern kbd_map_keyword_t kbd_map_keyword;

extern kbd_ans_t* ans;//pointer for kbd_ans come form kbd_scan

void KBD_REPORT_USB_INIT()
{
    report=kbd_report;

}


void KBD_REPORT_MAKE()
{
    uint8_t index;
    for(index=0;index<(ans->index);index++)
    {  
        report[index]=kbd_map_keyword[ans->map[index][0]][ans->map[index][1]];
        if(index>=REPORT_MAX)
        {
            break;
        }
        
    }
}