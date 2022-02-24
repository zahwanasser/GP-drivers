/*
 * timer.h
 *
 *  Created on: Feb 10, 2022
 *      Author: Zahwa Nasser
 *      Description: timer driver to configure it in periodic/one shot/ wait for trigger and synchronize mode
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
//typedef enum {
//    module0, module1,module2, module3, module4, module5,
//}timer_module;

typedef enum {
    timerA, timerB
}timer; //enum to choose timerA or timerB
typedef enum {
    periodic, oneShot,matching,waitForTrigger //wait for trigger starts from timberB module0
}timer_mode; //enum to choose timer mode


typedef struct { //configuration struct
//    timer_module module;
    timer timer; //choose timer
    timer_mode mode; //choose mode
    uint16 timer_startValue; //startting value
    uint16 timer_matchingValue; //matching value
    uint8 prescalar; //prescalar value

}timer16_configStruct;
typedef struct {
//    timer_module module;
    timer timer;
    timer_mode mode;
    uint32 timer_startValue;
    uint32 timer_matchingValue;
    uint16 prescalar;

}timer32_configStruct;
typedef struct {
//    timer_module module;
    timer timer;
    timer_mode mode;
    uint64 timer_startValue;
    uint64 timer_matchingValue;
    uint16 prescalar;

}timer64_configStruct;
typedef enum {
    module0_timerA= 1<<0,
    module0_timerB= 2<<0,
    Module0_timerAandB= 3<<0,
    module1_timerA= 1<<2,
    module1_timerB= 2<<2,
    module1_timerAandB= 3<<2,
    module2_timerA=1<<4,
    module2_timerB=2<<4,
    module2_timerAandB=3<<4,
    module3_timerA= 1<<6,
    module3_timerB= 2<<6,
    module3_timerAandB= 3<<6,
    module4_timerA= 1<<8,
    module4_timerB= 2<<8,
    module4_timerAandB = 3<<8,
    module5_timerA= 1<<10,
    module5_timerB= 2<<10,
    module5_timerAandB= 3<<10

}timer16_syncEnum;
typedef enum{
    timer16, timer32, timer64
}timer_size; //enum for disabling the timer
typedef struct {
    timer timer;
    timer_size size;
}timer_disableStruct; //struct to disable the timer
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void timer16_config(timer16_configStruct* timer16_configPtr);
void timer_disable(const timer_disableStruct* );
void timer32_config(const timer32_configStruct* timer32_config);

void timer64_config(const timer64_configStruct* timer64_config);
void timer_setCallBack(void(*a_ptr)(void));

void timer16_synchronize (timer16_syncEnum* timer16_sync); //we have to call this function each time we want to synchronize a new timer

#endif /* TIMER_H_ */
