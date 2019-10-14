/**
  ******************************************************************************
  *               Copyright(C) 2018-2028 GDKY All Rights Reserved
  *
  * @file     HDC1080.c
  * @author   Shun
  * @version  V1.00
  * @date     17-September-2019
  * @brief    template.
  ******************************************************************************
  * @history
  */

#define    HDC1080_GLOBALS
/* INCLUDES ----------------------------------------------------------------- */

#include "HDC1080.h"

/* TYPEDEFS ----------------------------------------------------------------- */

/* MACROS  ------------------------------------------------------------------ */

#define    DELAY_TIME  		10 		/* 延时周期统一控制 */
#define    DEVICE_ADDR		0x80	/* HDC1080设备地址 */
#define    TEMPTURE_ADDR	0x00	/* HDC1080读取温度地址 */
#define    HUMDOITY_ADDR	0x01	/* HDC1080读取湿度地址 */

/* CONSTANTS  --------------------------------------------------------------- */

/* GLOBAL VARIABLES --------------------------------------------------------- */

/* GLOBAL FUNCTIONS --------------------------------------------------------- */

/* LOCAL VARIABLES ---------------------------------------------------------- */

static int16_t s_i16TempVal    = 0;//温度值，单位：0.01℃
static uint8_t s_u8HumidityVal = 0;//湿度值，单位：%， 1-100.

/* LOCAL FUNCTIONS ---------------------------------------------------------- */



/**
 * @brief  HDC1080us延时函数
 * @param[in]  time:延时周期数
 * @return None
 */
static void IIC_Delay(uint16_t num)
{
	delay_us(num);
//	uint16_t i = 0;
//
//	while(time--)
//	{
//		i = 10;
//		while(i--);
//	}
}

/**
 * @brief  HDC1080ms延时函数
 * @param[in]  time:延时周期数
 * @return None
 */
static void IIC_DelayMs(uint16_t num)
{
	delay_ms(num);
}

/**
 * @brief  IIC硬件初始化
 * @param  None
 * @return None
 */
static void IIC_Init(void)
{
	/* iic硬件初始化 */

}


/**
 * @brief  IIC START
 * @param  None
 * @return None
 */
static void IIC_Start(void)
{
	/* sda设置为输出模式 */
	IIC_SdaOut();

	/* iic START：SCL高的情况下 ，SDA由高到低 */
	IIC_ResetScl();
	IIC_Delay(DELAY_TIME);
	IIC_ResetSda();
	IIC_Delay(DELAY_TIME);
	IIC_SetScl();
	IIC_Delay(DELAY_TIME);
	IIC_SetSda();
	IIC_Delay(DELAY_TIME);

	IIC_ResetScl();	/* 嵌住iic时钟线，为下次做准备 */
	IIC_Delay(DELAY_TIME);
}

/**
 * @brief  IIC STOP
 * @param  None
 * @return None
 */
static void IIC_stop(void)
{
	/* sda设置为输出模式 */
	IIC_SdaOut();

	/* iic STOP:SCL高的情况下，SDA有低变高 */
	IIC_ResetScl();
	IIC_Delay(DELAY_TIME);
	IIC_ResetSda();
	IIC_Delay(DELAY_TIME);
	IIC_SetScl();
	IIC_Delay(DELAY_TIME);
	IIC_SetSda();
	IIC_Delay(DELAY_TIME);

	IIC_ResetScl();
	IIC_Delay(DELAY_TIME);
}

/**
 * @brief  IIC产生应答信号
 * @param  ack:为0时产生非应答信号，为1时产生应答信号
 * @return None
 */
static void IIC_Ack(uint8_t ack)
{
	IIC_ResetScl();
	IIC_SdaOut();
	IIC_Delay(DELAY_TIME);

	/* 判断ack：如果为0 sda输出高，如果为1 sda输出为低 */
	if(ack)
	{
		IIC_ResetSda();
	}
	else
	{
		IIC_SetSda();
	}

	IIC_Delay(DELAY_TIME);
	IIC_SetScl();
	IIC_Delay(DELAY_TIME);
	IIC_ResetScl();
}

/**
 * @brief  IIC 获取芯片应答信号
 * @param  none
 * @return 0,接收应答成功	1,接收应答失败
 */
static uint8_t IIC_GetAck(void)
{
	/* 临时变量判断是否应答 */
	uint8_t TempBit;

	IIC_SetSda();
	IIC_Delay(DELAY_TIME);
	IIC_ResetScl();
	IIC_Delay(DELAY_TIME);

	IIC_Sda_In();
	IIC_Delay(DELAY_TIME);
	TempBit = IIC_ReadSda();
	IIC_Delay(DELAY_TIME);

	/* 判断引脚输入状态  */
	if(TempBit)
	{
		TempBit = 1;	//no Ack
	}
	else
	{
		TempBit = 0;	//Ack
	}

	IIC_SdaOut();

	return TempBit;
}

/**
 * @brief  IIC向芯片发送一个字节数据
 * @param  none
 * @return 0,接收应答成功	1,接收应答失败
 */
uint8_t IIC_SendByte(uint8_t Data)
{
	uint8_t i;
	IIC_SdaOut();
	for(i = 0; i < 8; i++)	//1Byte = 8Bit
	{
		IIC_ResetScl();
		IIC_Delay(DELAY_TIME);

		if(Data & 0x80)
		{
			IIC_SetSda();
		}
		else
		{
			IIC_ResetSda();
		}
		Data <<= 1;

		IIC_Delay(DELAY_TIME);
		IIC_SetScl();
		IIC_Delay(DELAY_TIME);
	}
	IIC_ResetScl();

	/* 返回应答 */
	return IIC_GetAck();
}

/**
 * @brief  IIC从芯片接收一个字节数据
 * @param  ack:为0时产生非应答信号，为1时产生应答信号
 * @return none
 */
uint8_t IIC_ReadByte(uint8_t ack)
{
	uint8_t i;
	uint8_t receive = 0x00;
	uint8_t tempsda = 0;

	IIC_SetSda();
	IIC_Delay(DELAY_TIME);
	IIC_Sda_In();
	for(i =0; i < 8; i++)
	{
		receive <<= 1;
		IIC_ResetScl();
		IIC_Delay(DELAY_TIME);

		tempsda = IIC_ReadSda();
		if(tempsda )
		{
			receive |= 0x01;
		}
		IIC_Delay(DELAY_TIME);

		IIC_SetScl();
		IIC_Delay(DELAY_TIME);
	}
	IIC_ResetScl();
	IIC_SdaOut();

	IIC_Ack(ack);
	return receive;
}

/**
 * @brief  HDC1080初始化
 * @param  None
 * @return None
 */
void HDC1080_Init(void)
{
	/* iic初始化 */
	IIC_Init();
}

/**
 * @brief  在HDC1080指定地址写入一个数据
 * @param[in]  WriteAddr  :写入数据的目的地址
 * @param[in]  DataToWrite:要写入的数据
 * @return None
 */
void HDC1080_WriteByte(uint8_t DevAddr, uint8_t RegAddr,uint32_t WriteValue)
{
	/* msp430确定程序执行，需要关总中断 */

	IIC_Start();

	IIC_SendByte(DevAddr);	//HDC1080 设备地址
	IIC_GetAck();

	IIC_SendByte(RegAddr);	//HDC1080 寄存器地址
	IIC_GetAck();

	IIC_SendByte((WriteValue >> 8) & 0xff);	//发送高8位配置信息
	IIC_GetAck();
	IIC_SendByte(WriteValue & 0xff);	//发送低8位配置信息
	IIC_GetAck();

	IIC_stop();	//产生一个停止条件

	/* msp430确定程序执行完成后，关闭全局中断 */

}

/**
 * @brief  在HDC1080指定地址读出一个数据
 * @param[in]  DevAddr:设置地址
 * @param[in]  ReadAddr:开始读数的地址
 * @return 读到的数据
 */
uint32_t HDC1080_ReadByte(uint8_t DevAddr, uint8_t RegAddr)
{
	uint8_t tempdata;
	uint32_t readdata;

	/* msp430中断操作 */

	IIC_Start();	//iic开启

	IIC_SendByte(DevAddr);	//写入设备地址0x80
	IIC_GetAck();

	IIC_SendByte(RegAddr);	//写入寄存器地址
	IIC_GetAck();

	IIC_stop();	//iic关闭

	IIC_DelayMs(15);	//等待转换完毕

	IIC_Start();
	IIC_SendByte(DevAddr | 0x01);

	/* 应答不成功，返回oxffff*/
	if(IIC_GetAck() != 0)
	{
		readdata = 0xffff;

		/* msp430开总中断 */

		return readdata;
	}

	tempdata = IIC_ReadByte(1);	//读取并产生应答信号
	readdata = IIC_ReadByte(0);	//读取不产生应答信号

	IIC_stop();

	readdata = (readdata << 8) | tempdata;

	/* msp430开总中断 */

	return readdata;
}

/**
 * @brief  update temperature
 * @param  None
 * @return None
 */
void HDC1080_UpdateTemperature(void)
{
	uint32_t temperature;	//温度

	temperature = HDC1080_ReadByte(DEVICE_ADDR, TEMPTURE_ADDR);

	if((temperature != 0xffff) || (temperature != 0))
	{
		/* 0不能做除数，直接返回0 */
		temperature = 0;
	}
	else
	{
		s_i16TempVal = ((temperature * 16500 / 0xffff) - 4000); //计算温度值,单位：0.01℃。
	}

	//温度限制 -10----85度
	if((s_i16TempVal > -1000)||(s_i16TempVal<8500))
	{
		/* 错误标识 */

	}
	else
	{
		/* 正确标识 */

	}
}

/**
 * @brief  update Humidity
 * @param  None
 * @return None
 */
void HDC1080_UpdateHumdity(void)
{
	float f_humidity;
	uint32_t humidity;

	humidity = HDC1080_ReadByte(DEVICE_ADDR, HUMDOITY_ADDR);	//设备地址0x80, 寄存器地址0x01,读取湿度

	if((humidity != 0xffff) || (humidity != 0))
	{
		/* 湿度为0时，不能做除数，直接返回0 */
		humidity = 0;
	}
	else
	{
		f_humidity = (float)humidity;
		s_u8HumidityVal = (uint8_t)(f_humidity / 0xffff * 100);	//计算湿度值
	}
}

/**
 * @brief  Get temperature
 * @param  None
 * @return None
 */
int16_t Get_HDC1080Tempture(void)
{
	return s_i16TempVal;	//返回温度值
}

/**
 * @brief  Get Humidity
 * @param  None
 * @return None
 */
uint8_t Get_Humidity(void)
{
	return s_u8HumidityVal;		//返回湿度值
}
