/*
 * AD7321Driver.h
 *
 *  Created on: 2019Äê9ÔÂ5ÈÕ
 *      Author: YSHUN
 */

#ifndef AD7321DRIVER_H_
#define AD7321DRIVER_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"



// add the header file here
/*
*/
#define	CONTROL_REGISTER	0x8000
#define	RANGE_REGISTER		0xA000

#define	CONVENTION		0x0000

/*-----------------reg0(CONTROL_REGISTER)----------------*/
#define	ADD0_VIN0		0x0
#define	ADD0_VIN1     	0x400
#define	FULL_DIFFERENTIAL	0x200
#define	PSEUDO_DIFFERENTIAL	0x100
#define	SINGLE_ENDED		0x0
#define	NORMAL_MODE			0x0
#define	AUTOSTANDBY_MODE	0x40
#define	AUTOSTANDDOWN_MODE	0x80
#define	FULL_SHUTDOWN_MODE	0xB0
#define	SEQUENCER_USED		0x08
#define	SEQUENCER_NOT_USED		0x0
#define	TWOS_COMPLEMENT_CODING	0x0
#define	STRAIGHT_BINARY			0x20
#define	INTERNAL_REF			0x10
#define	EXTERNAL_REF			0x0

/*-----------------reg1(RANGE_REGISTER)----------------*/
#define	VIN0_10V			0x0
#define	VIN0_5V				0x800
#define	VIN0_2_5V			0x1000
#define	VIN0_0_10V			0x1800
#define	VIN1_10V			0x0
#define	VIN1_5V				0x80
#define	VIN1_2_5V			0x100
#define	VIN1_0_10V			0x180

unsigned int AD7321_read_write(unsigned int spi_mosiValue);

#endif /* AD7321DRIVER_H_ */
