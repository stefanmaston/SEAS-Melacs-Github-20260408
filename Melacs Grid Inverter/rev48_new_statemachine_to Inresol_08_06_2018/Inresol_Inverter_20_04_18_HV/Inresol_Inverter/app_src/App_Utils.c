/*
 *  File name: App_Utils.c
 *
 *  Description: High level Utility functions
 *
 *  Author: Future Electronics
 *
 */

#include <string.h>
#include "global_includes.h"

//*****************************************************************************
//***************************** ASCII - HEX ***********************************
//*****************************************************************************

static uint8_t asciihex_1_to_nibble(char *ascii_ptr)
{
	uint8_t nibble;
	uint8_t ret_val = 0;

	nibble = *ascii_ptr;
	if((nibble >= '0') && (nibble <= '9')) {
		ret_val = nibble - '0';
	} else if((nibble >= 'a') && (nibble <= 'f')) {
		ret_val = nibble - 'a' + 10;
	} else if((nibble >= 'A') && (nibble <= 'F')) {
		ret_val = nibble - 'A' + 10;
	}
	return ret_val;
}

static uint8_t asciihex_1_to_nibble_incptr(char **ascii_ptr)
{
	uint8_t nibble;
	uint8_t ret_val = 0;

	nibble = **ascii_ptr;
	if((nibble >= '0') && (nibble <= '9')) {
		ret_val = nibble - '0';
	} else if((nibble >= 'a') && (nibble <= 'f')) {
		ret_val = nibble - 'a' + 10;
	} else if((nibble >= 'A') && (nibble <= 'F')) {
		ret_val = nibble - 'A' + 10;
	}
	(*ascii_ptr)++;
	return ret_val;
}

uint8_t asciihex_2_to_uint8(char *ascii_ptr)
{
	uint8_t nibble_1, nibble_0;
	uint8_t ret_val;

	nibble_1 = asciihex_1_to_nibble(ascii_ptr);
	ascii_ptr++;
	nibble_0 = asciihex_1_to_nibble(ascii_ptr);
	ret_val = (nibble_1 << 4) | (nibble_0 << 0);
	return ret_val;
}

uint8_t asciihex_2_to_uint8_incptr(char **ascii_ptr)
{
	uint8_t nibble_1, nibble_0;
	uint8_t ret_val;

	nibble_1 = asciihex_1_to_nibble_incptr(ascii_ptr);
	nibble_0 = asciihex_1_to_nibble_incptr(ascii_ptr);
	ret_val = (nibble_1 << 4) | (nibble_0 << 0);
	return ret_val;
}

void asciihex_2_to_uint8_inc2ptrs(char **ascii_ptr, uint8_t **bin_ptr)
{
	uint8_t nibble_1, nibble_0;
	uint8_t ret_val;

	nibble_1 = asciihex_1_to_nibble_incptr(ascii_ptr);
	nibble_0 = asciihex_1_to_nibble_incptr(ascii_ptr);
	ret_val = (nibble_1 << 4) | (nibble_0 << 0);
	*((uint8_t*)*bin_ptr) = ret_val;
	*bin_ptr += 1;
}

uint16_t asciihex_4_to_uint16(char *ascii_ptr)
{
	uint8_t nibble_3, nibble_2, nibble_1, nibble_0;
	uint16_t ret_val;

	nibble_3 = asciihex_1_to_nibble(ascii_ptr);
	ascii_ptr++;
	nibble_2 = asciihex_1_to_nibble(ascii_ptr);
	ascii_ptr++;
	nibble_1 = asciihex_1_to_nibble(ascii_ptr);
	ascii_ptr++;
	nibble_0 = asciihex_1_to_nibble(ascii_ptr);
	ret_val = (nibble_3 << 12) | (nibble_2 << 8) | (nibble_1 << 4) | (nibble_0 << 0);
	return ret_val;
}

uint16_t asciihex_4_to_uint16_incptr(char **ascii_ptr)
{
	uint8_t nibble_3, nibble_2, nibble_1, nibble_0;
	uint16_t ret_val;

	nibble_3 = asciihex_1_to_nibble_incptr(ascii_ptr);
	nibble_2 = asciihex_1_to_nibble_incptr(ascii_ptr);
	nibble_1 = asciihex_1_to_nibble_incptr(ascii_ptr);
	nibble_0 = asciihex_1_to_nibble_incptr(ascii_ptr);
	ret_val = (nibble_3 << 12) | (nibble_2 << 8) | (nibble_1 << 4) | (nibble_0 << 0);
	return ret_val;
}

void asciihex_4_to_uint16_inc2ptrs(char **ascii_ptr, uint8_t **bin_ptr)
{
	uint8_t nibble_3, nibble_2, nibble_1, nibble_0;
	uint16_t ret_val;

	nibble_3 = asciihex_1_to_nibble_incptr(ascii_ptr);
	nibble_2 = asciihex_1_to_nibble_incptr(ascii_ptr);
	nibble_1 = asciihex_1_to_nibble_incptr(ascii_ptr);
	nibble_0 = asciihex_1_to_nibble_incptr(ascii_ptr);
	ret_val = (nibble_3 << 12) | (nibble_2 << 8) | (nibble_1 << 4) | (nibble_0 << 0);
	*((uint16_t*)*bin_ptr) = ret_val;
	*bin_ptr += 2;
}

uint32_t asciihex_8_to_uint32(char *ascii_ptr)
{
	uint16_t word_1, word_0;
	uint32_t ret_val;

	word_1 = asciihex_4_to_uint16(ascii_ptr);
	ascii_ptr += 4;
	word_0 = asciihex_4_to_uint16(ascii_ptr);
	ret_val = ((uint32_t)word_1 << 16) | (word_0 << 0);
	return ret_val;
}

uint32_t asciihex_8_to_uint32_incptr(char **ascii_ptr)
{
	uint16_t word_1, word_0;
	uint32_t ret_val;

	word_1 = asciihex_4_to_uint16_incptr(ascii_ptr);
	word_0 = asciihex_4_to_uint16_incptr(ascii_ptr);
	ret_val = ((uint32_t)word_1 << 16) | (word_0 << 0);
	return ret_val;
}

void asciihex_8_to_uint32_inc2ptrs(char **ascii_ptr, uint8_t **bin_ptr)
{
	uint16_t word_1, word_0;
	uint32_t ret_val;

	word_1 = asciihex_4_to_uint16_incptr(ascii_ptr);
	word_0 = asciihex_4_to_uint16_incptr(ascii_ptr);
	ret_val = ((uint32_t)word_1 << 16) | (word_0 << 0);
	*((uint32_t*)*bin_ptr) = ret_val;
	*bin_ptr += 4;
}

/*
char* uint8_to_asciihex(uint8_t data, char *asciihex_ptr)
{
	uint8_t nibble;

	nibble = (data >> 4) & 0x0F;
	if((nibble >= 0x00) && (nibble <= 0x09)) {
		*asciihex_ptr = nibble + '0';
	} else if((nibble >= 0x0A) && (nibble <= 0x0F)) {
		*asciihex_ptr = nibble + ('A' - 0x0A);
	}
	asciihex_ptr++;
	nibble = (data >> 0) & 0x0F;
	if((nibble >= 0x00) && (nibble <= 0x09)) {
		*asciihex_ptr = nibble + '0';
	} else if((nibble >= 0x0A) && (nibble <= 0x0F)) {
		*asciihex_ptr = nibble + ('A' - 0x0A);
	}
	asciihex_ptr++;
	return asciihex_ptr;
}
*/

void uint8_to_asciihex_2_incptr(uint8_t bin_data, char **ascii_ptr)
{
	uint8_t nibble;

	nibble = (bin_data >> 4) & 0x0F;
	if((nibble >= 0x00) && (nibble <= 0x09)) {
		*((uint8_t*)*ascii_ptr) = nibble + '0';
	} else if((nibble >= 0x0A) && (nibble <= 0x0F)) {
		*((uint8_t*)*ascii_ptr) = nibble + ('A' - 0x0A);
	}
	*ascii_ptr += 1;
	nibble = (bin_data >> 0) & 0x0F;
	if((nibble >= 0x00) && (nibble <= 0x09)) {
		*((uint8_t*)*ascii_ptr) = nibble + '0';
	} else if((nibble >= 0x0A) && (nibble <= 0x0F)) {
		*((uint8_t*)*ascii_ptr) = nibble + ('A' - 0x0A);
	}
	*ascii_ptr += 1;
}

void uint16_to_asciihex_4_incptr(uint16_t bin_data, char **ascii_ptr)
{
	uint8_t byte_1, byte_0;
	
	byte_1 = bin_data >> 8;
	byte_0 = bin_data >> 0;
	uint8_to_asciihex_2_incptr(byte_1, ascii_ptr);
	uint8_to_asciihex_2_incptr(byte_0, ascii_ptr);
}

void uint32_to_asciihex_8_incptr(uint32_t bin_data, char **ascii_ptr)
{
	uint8_t byte_3, byte_2, byte_1, byte_0;
	
	byte_3 = bin_data >> 24;
	byte_2 = bin_data >> 16;
	byte_1 = bin_data >> 8;
	byte_0 = bin_data >> 0;
	uint8_to_asciihex_2_incptr(byte_3, ascii_ptr);
	uint8_to_asciihex_2_incptr(byte_2, ascii_ptr);
	uint8_to_asciihex_2_incptr(byte_1, ascii_ptr);
	uint8_to_asciihex_2_incptr(byte_0, ascii_ptr);
}

void uint8_to_asciihex_2_inc2ptrs(uint8_t **bin_ptr, char **ascii_ptr)
{
	uint8_t byte;
	
	byte = *((uint8_t*)*bin_ptr);
	*bin_ptr += 1;
	uint8_to_asciihex_2_incptr(byte, ascii_ptr);
}

void uint16_to_asciihex_4_inc2ptrs(uint8_t **bin_ptr, char **ascii_ptr)
{
	uint16_t word;
	
	word = *((uint16_t*)*bin_ptr);
	*bin_ptr += 2;
	uint16_to_asciihex_4_incptr(word, ascii_ptr);
}

void uint32_to_asciihex_8_inc2ptrs(uint8_t **bin_ptr, char **ascii_ptr)
{
	uint32_t dword;
	
	dword = *((uint32_t*)*bin_ptr);
	*bin_ptr += 4;
	uint32_to_asciihex_8_incptr(dword, ascii_ptr);
}
