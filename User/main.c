#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "Timer.h"
#include "OLED.h"
#include "jiema.h"

uint8_t Serial_TxData[8]={0x01,0x04,0x00,0x00,0x00,0x02,0x71,0xCB};	//定义串口发送的数据数组

int main(void)
{
	Timer_Init();		//初始化定时器
	Serial_Init();		//初始化串口
	OLED_Init();		//初始化OLED

	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Tem:");
	OLED_ShowString(2, 1, "Hum:");

	ModeI();			//初始化为接收模式
	while (1)
	{
		if(TxFlag==1)	//判断定时器标志位变量是否为1
		{	
			ModeO();	//切换为发送模式
			TxFlag=0;	//将定时器标志位变量清零
			Serial_SendArray(Serial_TxData, 8);	//调用串口发送数组函数，发送数据数组
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	//等最后一个字节真正发完
			ModeI();	//切换为接收模式
		}
		if(Serial_GetRxFlag())	//判断串口接收的标志位变量是否为1
		{
			jiema(Serial_RxData, RxLen);	//调用解码函数，传入接收数据数组和长度
			OLED_ShowSignedNum(1, 5, Tem / 10, 2);					//温度整数部分，占第 5~7 列
			OLED_ShowChar(1, 8, '.');								//小数点，第 8 列
			OLED_ShowNum(1, 9, (Tem >= 0 ? Tem : -Tem) % 10, 1);	//温度小数部分，第 9 列

			OLED_ShowSignedNum(2, 5, Hum / 10, 2);					//湿度整数部分
			OLED_ShowChar(2, 8, '.');								//小数点
			OLED_ShowNum(2, 9, Hum % 10, 1);						//湿度小数部分
		}

	}
}
