/******************************************************************************
* Released under the MIT Licence
* Copyright ADBeta (c) 2024
******************************************************************************/
#include "ch32v003fun.h"
#include "lib_rand.h"

#include <stdio.h>


uint32_t _lfsr = 0x747AA32F;

// Static/inline?
// Calculate the next most-significant-bit from the LFSR
uint32_t lfsr_next_msb(void)
{
	/*
	// Using bits 31 21 1 0 as feedback taps.
	uint32_t bit_31 = (_lfsr >> 31) & 0x01;
	uint32_t bit_21 = (_lfsr >> 21) & 0x01;
	uint32_t bit_01 = (_lfsr >> 1)  & 0x01;
	uint32_t bit_00 =  _lfsr        & 0x01;

	//return bit_31 ^ bit_21 ^ bit_01 ^ bit_00;
	uint32_t new_bit = (bit_31 ^ bit_21 ^ bit_01 ^ bit_00) << 31;
	_lfsr = (_lfsr >> 1) | new_bit;
	*/


	
	// Shifting to MSB to make calculations more efficient later
	uint32_t bit_31 = _lfsr         & 0x80000000;
	uint32_t bit_21 = (_lfsr << 10) & 0x80000000;
	uint32_t bit_01 = (_lfsr << 30) & 0x80000000;
	uint32_t bit_00 = (_lfsr << 31) & 0x80000000;

	//return bit_31 ^ bit_21 ^ bit_01 ^ bit_00;
	uint32_t new_bit = bit_31 ^ bit_21 ^ bit_01 ^ bit_00;
	_lfsr = (_lfsr >> 1) | new_bit;
	

	return new_bit;
}




int main() 
{
	SystemInit();


	for(int x = 0; x < 255; x++)
	{
		printf("0x%08X\n",   _lfsr);
		printf("0x%08X\n\n", lfsr_next_msb());
	}
	return 0;
}
