#ifndef __MODBUS_H
#define __MODBUS_H

#include "stm32f10x.h"

uint16_t Modbus_CRC16(uint8_t *puchMsg, uint16_t usDataLen);

#endif
