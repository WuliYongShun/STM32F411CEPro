/*
 * HDC1080.h
 *
 *  Created on: 2019��9��17��
 *      Author: S
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HDC1080_H_
#define HDC1080_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef   HDC1080_GLOBALS
#define  HDC1080_EXT
#else
#define  HDC1080_EXT  extern
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* TYPEDEFS ----------------------------------------------------------------- */

/* MACROS  ------------------------------------------------------------------ */

/* msp430ʱ������ */
#define CPU_F	((double)8000000)
#define	delay_us(us)  __delay_cycles((long)(CPU_F * (double)us / 1000000.0))   //__delay_cycles(1): delay time = 1 system clock.
#define	delay_ms(ms)  __delay_cycles((long)(CPU_F * (double)ms / 1000.0))

/* Private defines -----------------------------------------------------------*/
#define HDC1080_ADDR		0x80	/* HDC1080 IIC��ַ */

#define IIC_SCL_GPIO        /* sclʱ�����Ŷ˿ڶ��� */
#define IIC_SCL_PIN         /* sclʱ�����Ŷ���  */
#define IIC_SDA_GPIO        /* sda�������Ŷ˿ڶ��� */
#define IIC_SDA_PIN         /* sda�������Ŷ��� */

#define IIC_ResetScl()     /* iic sclʱ�������õ� */
#define IIC_SetScl()       /* iic sclʱ�������ø� */

#define IIC_ResetSda()     /* iic sda�����õ� */
#define IIC_SetSda()       /* iic sda�����ø� */

#define IIC_ReadSda()      1/* iic sda����״̬��ȡ���� */

#define IIC_Sda_In()  		   /* iic sda��������Ϊ����ģʽ */
#define IIC_SdaOut()		   /* iic sda��������Ϊ���ģʽ */

/* CONSTANTS  --------------------------------------------------------------- */

/* GLOBAL VARIABLES --------------------------------------------------------- */

/* GLOBAL FUNCTIONS --------------------------------------------------------- */

void HDC1080_Init(void);				//��ʼ��HDC1080

void HDC1080_UpdateTemperature(void);	//���´������¶�
void HDC1080_UpdateHumdity(void);		//���´�����ʪ��

int16_t Get_HDC1080Tempture(void);		//��ȡHDC1080�������¶Ȳ�����
uint8_t Get_Humidity(void);				//��ȡHDC1080������ʪ�Ȳ�����

/* LOCAL VARIABLES ---------------------------------------------------------- */

/* LOCAL FUNCTIONS ---------------------------------------------------------- */



#ifdef __cplusplus
}
#endif

#endif /* HDC1080_H_ */
