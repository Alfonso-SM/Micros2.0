/*
 * BCD.c
 *
 *  Created on: 14 nov. 2019
 *      Author: lucky
 */

typedef unsigned char uint8;
typedef unsigned short uint16;

int BCD_vfnConvertion (uint16 u16FullVal)
{
	uint8 u8Decimal = 0;
	uint8 u8Unidad = 0;
	uint8 u8Centena = 0;

	u8Centena = u16FullVal / 100;

	u8Decimal = u16FullVal % 100;

	u8Unidad = u8Decimal % 10;

	u8Decimal -= u8Unidad;

	u8Decimal /= 10;

}
