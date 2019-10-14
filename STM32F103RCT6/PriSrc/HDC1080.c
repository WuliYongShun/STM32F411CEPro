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

#define    DELAY_TIME  		10 		/* ��ʱ����ͳһ���� */
#define    DEVICE_ADDR		0x80	/* HDC1080�豸��ַ */
#define    TEMPTURE_ADDR	0x00	/* HDC1080��ȡ�¶ȵ�ַ */
#define    HUMDOITY_ADDR	0x01	/* HDC1080��ȡʪ�ȵ�ַ */

/* CONSTANTS  --------------------------------------------------------------- */

/* GLOBAL VARIABLES --------------------------------------------------------- */

/* GLOBAL FUNCTIONS --------------------------------------------------------- */

/* LOCAL VARIABLES ---------------------------------------------------------- */

static int16_t s_i16TempVal    = 0;//�¶�ֵ����λ��0.01��
static uint8_t s_u8HumidityVal = 0;//ʪ��ֵ����λ��%�� 1-100.

/* LOCAL FUNCTIONS ---------------------------------------------------------- */



/**
 * @brief  HDC1080us��ʱ����
 * @param[in]  time:��ʱ������
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
 * @brief  HDC1080ms��ʱ����
 * @param[in]  time:��ʱ������
 * @return None
 */
static void IIC_DelayMs(uint16_t num)
{
	delay_ms(num);
}

/**
 * @brief  IICӲ����ʼ��
 * @param  None
 * @return None
 */
static void IIC_Init(void)
{
	/* iicӲ����ʼ�� */

}


/**
 * @brief  IIC START
 * @param  None
 * @return None
 */
static void IIC_Start(void)
{
	/* sda����Ϊ���ģʽ */
	IIC_SdaOut();

	/* iic START��SCL�ߵ������ ��SDA�ɸߵ��� */
	IIC_ResetScl();
	IIC_Delay(DELAY_TIME);
	IIC_ResetSda();
	IIC_Delay(DELAY_TIME);
	IIC_SetScl();
	IIC_Delay(DELAY_TIME);
	IIC_SetSda();
	IIC_Delay(DELAY_TIME);

	IIC_ResetScl();	/* Ƕסiicʱ���ߣ�Ϊ�´���׼�� */
	IIC_Delay(DELAY_TIME);
}

/**
 * @brief  IIC STOP
 * @param  None
 * @return None
 */
static void IIC_stop(void)
{
	/* sda����Ϊ���ģʽ */
	IIC_SdaOut();

	/* iic STOP:SCL�ߵ�����£�SDA�еͱ�� */
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
 * @brief  IIC����Ӧ���ź�
 * @param  ack:Ϊ0ʱ������Ӧ���źţ�Ϊ1ʱ����Ӧ���ź�
 * @return None
 */
static void IIC_Ack(uint8_t ack)
{
	IIC_ResetScl();
	IIC_SdaOut();
	IIC_Delay(DELAY_TIME);

	/* �ж�ack�����Ϊ0 sda����ߣ����Ϊ1 sda���Ϊ�� */
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
 * @brief  IIC ��ȡоƬӦ���ź�
 * @param  none
 * @return 0,����Ӧ��ɹ�	1,����Ӧ��ʧ��
 */
static uint8_t IIC_GetAck(void)
{
	/* ��ʱ�����ж��Ƿ�Ӧ�� */
	uint8_t TempBit;

	IIC_SetSda();
	IIC_Delay(DELAY_TIME);
	IIC_ResetScl();
	IIC_Delay(DELAY_TIME);

	IIC_Sda_In();
	IIC_Delay(DELAY_TIME);
	TempBit = IIC_ReadSda();
	IIC_Delay(DELAY_TIME);

	/* �ж���������״̬  */
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
 * @brief  IIC��оƬ����һ���ֽ�����
 * @param  none
 * @return 0,����Ӧ��ɹ�	1,����Ӧ��ʧ��
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

	/* ����Ӧ�� */
	return IIC_GetAck();
}

/**
 * @brief  IIC��оƬ����һ���ֽ�����
 * @param  ack:Ϊ0ʱ������Ӧ���źţ�Ϊ1ʱ����Ӧ���ź�
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
 * @brief  HDC1080��ʼ��
 * @param  None
 * @return None
 */
void HDC1080_Init(void)
{
	/* iic��ʼ�� */
	IIC_Init();
}

/**
 * @brief  ��HDC1080ָ����ַд��һ������
 * @param[in]  WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ
 * @param[in]  DataToWrite:Ҫд�������
 * @return None
 */
void HDC1080_WriteByte(uint8_t DevAddr, uint8_t RegAddr,uint32_t WriteValue)
{
	/* msp430ȷ������ִ�У���Ҫ�����ж� */

	IIC_Start();

	IIC_SendByte(DevAddr);	//HDC1080 �豸��ַ
	IIC_GetAck();

	IIC_SendByte(RegAddr);	//HDC1080 �Ĵ�����ַ
	IIC_GetAck();

	IIC_SendByte((WriteValue >> 8) & 0xff);	//���͸�8λ������Ϣ
	IIC_GetAck();
	IIC_SendByte(WriteValue & 0xff);	//���͵�8λ������Ϣ
	IIC_GetAck();

	IIC_stop();	//����һ��ֹͣ����

	/* msp430ȷ������ִ����ɺ󣬹ر�ȫ���ж� */

}

/**
 * @brief  ��HDC1080ָ����ַ����һ������
 * @param[in]  DevAddr:���õ�ַ
 * @param[in]  ReadAddr:��ʼ�����ĵ�ַ
 * @return ����������
 */
uint32_t HDC1080_ReadByte(uint8_t DevAddr, uint8_t RegAddr)
{
	uint8_t tempdata;
	uint32_t readdata;

	/* msp430�жϲ��� */

	IIC_Start();	//iic����

	IIC_SendByte(DevAddr);	//д���豸��ַ0x80
	IIC_GetAck();

	IIC_SendByte(RegAddr);	//д��Ĵ�����ַ
	IIC_GetAck();

	IIC_stop();	//iic�ر�

	IIC_DelayMs(15);	//�ȴ�ת�����

	IIC_Start();
	IIC_SendByte(DevAddr | 0x01);

	/* Ӧ�𲻳ɹ�������oxffff*/
	if(IIC_GetAck() != 0)
	{
		readdata = 0xffff;

		/* msp430�����ж� */

		return readdata;
	}

	tempdata = IIC_ReadByte(1);	//��ȡ������Ӧ���ź�
	readdata = IIC_ReadByte(0);	//��ȡ������Ӧ���ź�

	IIC_stop();

	readdata = (readdata << 8) | tempdata;

	/* msp430�����ж� */

	return readdata;
}

/**
 * @brief  update temperature
 * @param  None
 * @return None
 */
void HDC1080_UpdateTemperature(void)
{
	uint32_t temperature;	//�¶�

	temperature = HDC1080_ReadByte(DEVICE_ADDR, TEMPTURE_ADDR);

	if((temperature != 0xffff) || (temperature != 0))
	{
		/* 0������������ֱ�ӷ���0 */
		temperature = 0;
	}
	else
	{
		s_i16TempVal = ((temperature * 16500 / 0xffff) - 4000); //�����¶�ֵ,��λ��0.01�档
	}

	//�¶����� -10----85��
	if((s_i16TempVal > -1000)||(s_i16TempVal<8500))
	{
		/* �����ʶ */

	}
	else
	{
		/* ��ȷ��ʶ */

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

	humidity = HDC1080_ReadByte(DEVICE_ADDR, HUMDOITY_ADDR);	//�豸��ַ0x80, �Ĵ�����ַ0x01,��ȡʪ��

	if((humidity != 0xffff) || (humidity != 0))
	{
		/* ʪ��Ϊ0ʱ��������������ֱ�ӷ���0 */
		humidity = 0;
	}
	else
	{
		f_humidity = (float)humidity;
		s_u8HumidityVal = (uint8_t)(f_humidity / 0xffff * 100);	//����ʪ��ֵ
	}
}

/**
 * @brief  Get temperature
 * @param  None
 * @return None
 */
int16_t Get_HDC1080Tempture(void)
{
	return s_i16TempVal;	//�����¶�ֵ
}

/**
 * @brief  Get Humidity
 * @param  None
 * @return None
 */
uint8_t Get_Humidity(void)
{
	return s_u8HumidityVal;		//����ʪ��ֵ
}
