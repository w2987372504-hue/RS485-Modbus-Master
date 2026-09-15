#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"  

extern uint8_t RxFlag;
extern uint8_t RxLen;
extern uint8_t TxFlag;
void Timer_Init(void);

#endif
