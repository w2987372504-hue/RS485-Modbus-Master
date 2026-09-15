#ifndef __JIEMA_H
#define __JIEMA_H
#include "stm32f10x.h"  

extern int16_t Tem, Hum;	//温湿度，单位 0.1，例如 253 表示 25.3
void jiema(uint8_t *arr, uint8_t len);
#endif
