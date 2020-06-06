/*
 * @Author: your name
 * @Date: 2020-06-03 21:47:23
 * @LastEditTime: 2020-06-06 18:00:10
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \kbd_scan\Src\kbd_scan.c
 */
#include "kbd_scan.h"
#include "tim.h"

//键盘扫描函数初始化
void KBD_SCAN_INIT(kbd_info_t mykbd_info)
{
    /**
     * 扫描初始化分如下几个过程
     * 扫描频率计时器TIM_SCAN初始化
     * 防抖计时器初始化
     * */
    KBD_SCAN_SCAN_TIM_INIT(mykbd_info.timer_scan);
    KBD_SCAN_RMJIT_TIM_INIT(mykbd_info.timer_rmjit);

    //初始化反馈值的指针
}

//键盘扫描开始
void KBD_SCAN_START()
{
    /**
     * 这段代码主要用来初始化相关变量和启动扫描
     * */
    //初始化相关变量
    answer.answer_arry_num = 0;

    //开始扫描
    KBD_SCAN_SCAN_MAIN(kbd_info.keymap_phy);
}

//键盘扫描结束
void KBD_SCAN_STOP()
{
}

//键盘扫描频率中断初始化
void KBD_SCAN_SCAN_TIM_INIT(tim_info_t m_timer)
{
    /**
     * 键盘扫描中断计时器中断函数
     * 本函数用来初始化计时器相关设置
     * */

    MX_TIM1_Init();
}

//键盘扫描频率中断开始
void KBD_SCAN_SCAN_TIM_START()
{
    /**
     * 开始过程其实就是计时器中断开始的过程
     * 在计时器中断回调函数中写入扫描相关信息
     * 本函数主要作用是使能计时器中断，启动计时器
     * 过程如下：
     * 使能扫描计时器
     * */
    HAL_TIM_Base_Start_IT(&htim1);
}

//键盘扫描频率中断停止
void KBD_SCAN_SCAN_TIM_STOP()
{
    HAL_TIM_Base_Stop_IT(&htim1);
}

//键盘去抖中断初始化
void KBD_SCAN_RMJIT_TIM_INIT(tim_info_t m_timer)
{
    MX_TIM2_Init();
}

//键盘去抖中断开始
void KBD_SCAN_RMJIT_TIM_START()
{
    HAL_TIM_Base_Start_IT(&htim2);
}

//键盘去抖中断重载
void KBD_SCAN_RMJIT_TIM_RELOAD(tim_info_t m_timer)
{
    HAL_TIM_Base_Stop_IT(&htim2);
    MX_TIM2_Init();
    HAL_TIM_Base_Start_IT(&htim2);
}

//键盘去抖中断停止
void KBD_SCAN_RMJIT_TIM_STOP()
{
    HAL_TIM_Base_Stop_IT(&htim2);
}

//扫描中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == (&htim1))
    {
        KBD_SCAN_START();
    }
    else if (htim == (&htim2))
    {
        KBD_SCAN_RMJIT_MAIN();
    }
}

//键盘扫描主要逻辑算法
uint8_t KBD_SCAN_SCAN_MAIN(keymap_phy_t m_keymap_phy)
{
    //扫描开始
    uint8_t row_now = 0;
    for (; row_now < ROW_NUM; row_now++)
    {
        if (KBD_SCAN_SCAN_ROW(m_keymap_phy.keymap_phy_col, m_keymap_phy.col_num[row_now], row_now) == 0)
        {
            break;
        }
    }
}

//扫描行的算法
uint8_t KBD_SCAN_SCAN_ROW(gpio_t *m_gpio_map_col, uint8_t col_num, uint8_t row_now)
{
    uint8_t col_now = 0;
    uint8_t key_press_col[col_num];
    for (; col_now < col_num; col_now++)
    {
        if (KBD_SCAN_GPIO_READ(m_gpio_map_col) == 1)
        {
            //记录列数
            answer.answer_col_arry[answer.answer_arry_num] = col_now;
            //记录行数
            answer.answer_row_arry[answer.answer_arry_num] = row_now;
            //记录相关gpio号待会防抖用
            answer.answer_gpio_arry[answer.answer_arry_num] = m_gpio_map_col;
            //自家变量
            answer.answer_arry_num++;

            //防抖计时器重载
            KBD_SCAN_RMJIT_TIM_RELOAD(kbd_info.timer_rmjit);
        }
        if (answer.answer_arry_num > 6)
        {
            return 0;
        }
    }
}

uint8_t KBD_SCAN_SCAN_EACH(gpio_t *m_answer)
{
    uint8_t gpio_status;
    gpio_status = KBD_SCAN_GPIO_READ(m_answer);
    return gpio_status;
}

//防抖逻辑算法
void KBD_SCAN_RMJIT_MAIN()
{
    answer.answer_arry_num = 0; //初始化引导
    for (; answer.answer_arry_num <= sizeof(answer.answer_gpio_arry); answer.answer_arry_num++)
    {
        if (KBD_SCAN_SCAN_EACH(answer.answer_gpio_arry[answer.answer_arry_num]) == 0)
        {
            answer.answer_row_arry[answer.answer_arry_num] = 0;
            answer.answer_col_arry[answer.answer_arry_num] = 0;
            answer.answer_gpio_arry[answer.answer_arry_num] = 0;
        }
    }
}

/**
 * 重写GPIO操作函数
 * 移植时请重写
 * */

//拉高GPIO
void KBD_SCAN_GPIO_UP(gpio_t *m_gpio)
{
    HAL_GPIO_WritePin(m_gpio->gpio_group, *m_gpio->gpio_pin, 1);
}

//拉低GPIO
void KBD_SCAN_GPIO_DW(gpio_t *m_gpio)
{
    HAL_GPIO_WritePin(m_gpio->gpio_group, *m_gpio->gpio_pin, 0);
}

//读取GPIO
uint8_t KBD_SCAN_GPIO_READ(gpio_t *m_gpio)
{
    uint8_t gpio_status = 0;
    gpio_status = HAL_GPIO_ReadPin(m_gpio->gpio_group, *m_gpio->gpio_pin);
    return gpio_status;
}
