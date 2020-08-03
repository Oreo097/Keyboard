// /*
//  * @Descripttion: 这是用来生成和输出report的文件，主要应该包含是否输出report的判断，和report组成，report传输部分
//  * @version: 
//  * @Author: Oreo097
//  * @Date: 2020-07-11 16:26:25
//  * @LastEditors: Oreo097
//  * @LastEditTime: 2020-07-28 21:52:49
//  */ 
// #include "kbd_report.h"


// /**
//  * @name: Oreo097
//  * @msg: 6KRO的报告，用于USB HID发送
//  * @param {type} 
//  * @return: 
//  */
// kbd_report_t kbd_report_report_6[8];

// /**
//  * @name: Oreo097
//  * @msg: 6KRO的扫描结果的指针
//  * @param {type} 
//  * @return: 
//  */
// extern kbd_scan_ans_t * kbd_scan_ans_ptr;

// /**
//  * @name: Oreo097
//  * @msg: akey的键值表
//  * @param {type} 
//  * @return: 
//  */
// extern kdb_map_keywords_t * kbd_map_keywords_key_ptr;


// /**
//  * @name: Oreo097
//  * @msg: 检查扫描结果是否需要生成report
//  * @param {kbd_scan_ans_t * 扫描结果} 
//  * @return: 如果需要生成并发送reprot返回true，否则返回false
//  */
// bool KBD_REPORT_CHECK_ANS(kbd_scan_ans_t * ans)
// {
//     if(ans->changed==true)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }

// /**
//  * @name: Oreo097
//  * @msg: 生成report的函数,6KRO专用
//  * @param {kbd_scan_ans_t * 扫描结果} 
//  * @return: void
//  */
// void KBD_REPROT_MAKE_6KRO(kbd_scan_ans_t * ans,kbd_map_keywords_t keyword)
// {

// }

// /**
//  * @name: Oreo097
//  * @msg: 生成SKEY的report的函数,6KRO专用
//  * @param {kbd_scan_ans_t * 扫描结果,kbd_map_keyword_t * 键值表,kbd_report_t* 报表} 
//  * @return: void
//  */
// void KBD_REPROT_MAKE_SKEY_6KRO(kbd_scan_ans_t * ans,kbd_map_keywords_t * keyword,kbd_report_t * report)
// {
//     for(uint8_t index_skey=0;index_skey<ans->index_fkey;index_skey++)
//     {
//         *report;
//     }
// }

// /**
//  * @name: Oreo097
//  * @msg: 生成AKEY的report的函数，6KRO专用
//  * @param {kbd_scan_ans_t * 扫描结果,kbd_map_keyword_t * 键值表,kbd_report_t * 报告} 
//  * @return: 
//  */
// void KBD_REPORT_MAKE_AKEY_6KRO(kbd_scan_ans_t * ans,kbd_map_keywords_t * keyword,kbd_report_t * report)
// {
//     report+=(2*sizeof(uint8_t));
//     for(uint8_t index_akey=(SKEY_MAX+FKEY_MAX);index_akey<REPORT_MAX_6;index_akey++)
//     {
//         if(ans->array[index_akey][0]==0xff)
//         {
//             continue;
//         }
//         *report=keyword->keymap[ans->array[index_akey][0]][ans->array[index_akey][1]];
//         report++;
//     }
// }

// /**
//  * @name: Oreo097
//  * @msg: FKEY的循环切换，6KRO专用
//  * @param {kbd_scan_ans_t * 结果,kbd_map_keyword_t 键值表,kbd_report_t * 报告} 
//  * @return: 
//  */
// void KBD_REPORT_KMAP_SWITCH_6KRO(kbd_scan_ans_t * ans,kbd_map_keywords_t keyword,kbd_report_t * report)
// {

// }

// /**
//  * @name: Oreo097
//  * @msg: FKEY的多键键层切换，6KRO专用
//  * @param {kbd_scan_ans_t * 结果,kbd_map_keyword_t 键值表,kbd_report_t * 报告} 
//  * @return: void
//  */
// void KBD_REPORT_KEMAP_SWITCHS_6KRO(kbd_scan_ans_t * ans,kbd_map_keywords_t * keyword,kbd_report_t * report)
// {

// }

// /**
//  * @name: Oreo097
//  * @msg: 通过USB hid发送report的函数
//  * @param {kbd_scan_ans_t * 结果,kbd_map_keyword_t 键值表,kbd_report_t * 报告} 
//  * @return: void
//  */
// void KBD_REPORT_SEND(kbd_report_t report)
// {

// }
