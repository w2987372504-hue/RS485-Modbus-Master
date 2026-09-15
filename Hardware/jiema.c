#include "jiema.h"
#include "Modbus.h"

int16_t Tem, Hum; //定义温湿度变量，单位 0.1，例如 253 表示 25.3
void jiema(uint8_t *arr, uint8_t len)
{
    uint16_t crc,Tem1 ;
    
    if(arr[0] != 0x01)
    {
        return; // Invalid address, exit the function
    }
    else
    {
        crc = Modbus_CRC16(arr,len-2);   // 只算前 7 字节
        if ((crc & 0xFF) == arr[len-2] && (crc >> 8) == arr[len-1])
        {
            Tem1=(arr[3]<<8)|arr[4];
            Hum=(arr[5]<<8)|arr[6];
            if(Tem1<10000)
            {
                Tem=Tem1;
            }
            else
            {
                Tem=-(Tem1-10000);
            }
        }
        else
        {
            return;
        }
    }   
}
