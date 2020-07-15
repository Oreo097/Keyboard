/*
 * @Descripttion: 这是用来生成和输出report的文件，主要应该包含是否输出report的判断，和report组成，report传输部分
 * @version: 
 * @Author: Oreo097
 * @Date: 2020-07-11 16:26:25
 * @LastEditors: Oreo097
 * @LastEditTime: 2020-07-15 12:55:34
 */ 
#include "kbd_report.h"






/**
 * @name: Oreo097
 * @msg: 生成report的函数,6KRO专用
 * @param {kbd_scan_ans_t * 扫描结果} 
 * @return: void
 */
void KBD_REPROT_MAKE_6KRO(kbd_scan_ans_t * ans,kbd_map_keyword_t keyword)
{
    for(uint8_t index_fkey;index_fkey<ans->index_fkey;index_fkey++)
    {

    }
}

/**
 * @name: Oreo097
 * @msg: 检查扫描结果是否需要生成report
 * @param {kbd_scan_ans_t * 扫描结果} 
 * @return: 如果需要生成并发送reprot返回true，否则返回false
 */
bool KBD_REPORT_CHECK_ANS_FKEY(kbd_scan_ans_t * ans)
{
    
}