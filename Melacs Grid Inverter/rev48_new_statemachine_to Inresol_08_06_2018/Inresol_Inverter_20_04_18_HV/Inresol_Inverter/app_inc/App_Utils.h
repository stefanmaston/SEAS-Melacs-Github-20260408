/*
 *  File name: App_Utils.h
 *
 *  Description: High level Utility function declarations
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_UTILS_H
#define APP_UTILS_H

//*****************************************************************************
//***************************** ASCII - HEX ***********************************
//*****************************************************************************

uint8_t asciihex_2_to_uint8(char *ascii_ptr);
uint16_t asciihex_4_to_uint16(char *ascii_ptr);
uint32_t asciihex_8_to_uint32(char *ascii_ptr);

uint8_t asciihex_2_to_uint8_incptr(char **ascii_ptr);
uint16_t asciihex_4_to_uint16_incptr(char **ascii_ptr);
uint32_t asciihex_8_to_uint32_incptr(char **ascii_ptr);

void asciihex_2_to_uint8_inc2ptrs(char **ascii_ptr, uint8_t **bin_ptr);
void asciihex_4_to_uint16_inc2ptrs(char **ascii_ptr, uint8_t **bin_ptr);
void asciihex_8_to_uint32_inc2ptrs(char **ascii_ptr, uint8_t **bin_ptr);

//char* uint8_to_asciihex(uint8_t data, char *asciihex_ptr);

void uint8_to_asciihex_2_incptr(uint8_t bin_data, char **ascii_ptr);
void uint16_to_asciihex_4_incptr(uint16_t bin_data, char **ascii_ptr);
void uint32_to_asciihex_8_incptr(uint32_t bin_data, char **ascii_ptr);

void uint8_to_asciihex_2_inc2ptrs(uint8_t **bin_ptr, char **ascii_ptr);
void uint16_to_asciihex_4_inc2ptrs(uint8_t **bin_ptr, char **ascii_ptr);
void uint32_to_asciihex_8_inc2ptrs(uint8_t **bin_ptr, char **ascii_ptr);

#endif // APP_UTILS_H
