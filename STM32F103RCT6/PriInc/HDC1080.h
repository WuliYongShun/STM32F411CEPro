/*
 * HDC1080.h
 *
 *  Created on: 2019年9月17日
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

/* msp430时钟配置 */
#define CPU_F	((double)8000000)
#define	delay_us(us)  __delay_cycles((long)(CPU_F * (double)us / 1000000.0))   //__delay_cycles(1): delay time = 1 system clock.
#define	delay_ms(ms)  __delay_cycles((long)(CPU_F * (double)ms / 1000.0))

/* Private defines -----------------------------------------------------------*/
#define HDC1080_ADDR		0x80	/* HDC1080 IIC地址 */

#define IIC_SCL_GPIO        /* scl时钟引脚端口定义 */
#define IIC_SCL_PIN         /* scl时钟引脚定义  */
#define IIC_SDA_GPIO        /* sda数据引脚端口定义 */
#define IIC_SDA_PIN         /* sda数据引脚定义 */

#define IIC_ResetScl()     /* iic scl时钟引脚置低 */
#define IIC_SetScl()       /* iic scl时钟引脚置高 */

#define IIC_ResetSda()     /* iic sda引脚置低 */
#define IIC_SetSda()       /* iic sda引脚置高 */

#define IIC_ReadSda()      1/* iic sda输入状态读取数据 */

#define IIC_Sda_In()  		   /* iic sda引脚设置为输入模式 */
#define IIC_SdaOut()		   /* iic sda引脚设置为输出模式 */

/* CONSTANTS  --------------------------------------------------------------- */

/* GLOBAL VARIABLES --------------------------------------------------------- */

/* GLOBAL FUNCTIONS --------------------------------------------------------- */

void HDC1080_Init(void);				//初始化HDC1080

void HDC1080_UpdateTemperature(void);	//更新传感器温度
void HDC1080_UpdateHumdity(void);		//更新传感器湿度

int16_t Get_HDC1080Tempture(void);		//获取HDC1080传感器温度并返回
uint8_t Get_Humidity(void);				//获取HDC1080传感器湿度并返回

/* LOCAL VARIABLES ---------------------------------------------------------- */

/* LOCAL FUNCTIONS ---------------------------------------------------------- */



#ifdef __cplusplus
}
#endif

#endif /* HDC1080_H_ */
