#include "Modbus.h"

/**
  * 函    数：计算 Modbus RTU 的 CRC16 校验值
  * 参    数：puchMsg  要计算的数据首地址
  * 参    数：usDataLen 数据长度，单位字节
  * 返 回 值：CRC16 校验值
  * 算    法：CRC-16/MODBUS，多项式 0x8005（反转后为 0xA001），初值 0xFFFF
  * 注意事项：返回的是 16 位数值，上线时低字节在前、高字节在后，
  *           即先发 (crc & 0xFF)，再发 (crc >> 8)
  *           变量名必须用小写 crc：stm32f10x.h 里已把 CRC 定义成外设指针宏，
  *           写成大写会被宏替换，整个函数编译不过
  */
uint16_t Modbus_CRC16(uint8_t *puchMsg, uint16_t usDataLen)
{
	uint16_t crc = 0xFFFF;		//CRC 初值，Modbus 规定固定为 0xFFFF
	uint8_t i;

	while (usDataLen --)		//遍历每一个字节
	{
		crc ^= *puchMsg ++;		//把当前字节异或到 crc 的低字节

		for (i = 0; i < 8; i ++)	//对该字节的 8 位逐位处理
		{
			if (crc & 0x0001)			//如果最低位是 1
			{
				crc = (crc >> 1) ^ 0xA001;	//右移一位后异或多项式
			}
			else						//如果最低位是 0
			{
				crc >>= 1;					//只右移一位
			}
		}
	}
	return crc;
}
