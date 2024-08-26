/******************************************************************************
* Released under the MIT Licence
* Copyright ADBeta (c) 2024
******************************************************************************/
#include "ch32v003fun.h"
#include "lib_rand.h"

#include <stdio.h>

#define RANDOM_STRENGTH 2


uint32_t _lfsr = 0x747AA32F;

// Static/inline?
// Calculate the next most-significant-bit from the LFSR
uint32_t lfsr_next_msb(void)
{
	// Shifting to MSB to make calculations more efficient later
	uint32_t bit_31 = _lfsr         & 0x80000000;
	uint32_t bit_21 = (_lfsr << 10) & 0x80000000;
	uint32_t bit_01 = (_lfsr << 30) & 0x80000000;
	uint32_t bit_00 = (_lfsr << 31) & 0x80000000;

	return bit_31 ^ bit_21 ^ bit_01 ^ bit_00;
}

uint32_t rand(void)
{
	uint32_t r_output = 0;

	// If RANDOM_STRENGTH is level 1, just Shift the register by 1
	#if RANDOM_STRENGTH == 1
	_lfsr = (_lfsr >> 1) | lfsr_next_msb();
	r_output = _lfsr;
	#endif

	// If RANDOM_STRENGTH is level 2, generate a new bit for all 32bits of
	// the output variable
	#if RANDOM_STRENGTH == 2
	uint8_t bits = 32;
	while(bits--)
	{
		// Get the next bit and update the LFSR
		uint32_t msb = lfsr_next_msb();
		_lfsr = (_lfsr >> 1) | msb;

		// Slip the new bit into the output
		r_output = r_output >> 1;
		r_output |= msb;
	}

	#endif

	return r_output;
}


int main() 
{
	SystemInit();


	for(int x = 0; x < 10; x++)
	{
		printf("0x%08X\n",   _lfsr);
		printf("0x%08X\n\n", rand());
	}
	return 0;
}
