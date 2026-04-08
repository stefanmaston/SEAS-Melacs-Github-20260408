#ifndef _INTTYPES_H
#define _INTTYPES_H

enum
{
	false,
	true
}
bool;


typedef signed char int8_t; 				// -128 -> 127				 // Char & Signed Char
typedef unsigned char uint8_t; 				// 0 -> 255					 // Unsigned Char
typedef signed short int int16_t; 			// -32768 -> 32767			 // Int
typedef unsigned short int uint16_t; 		// 0 -> 65535				 // Unsigned Int
typedef signed int int32_t; 		// -8388608 -> 8388607		 // Short Long
typedef unsigned int uint32_t;	// 0 -> 16777215			 // Unsigned Short Long
typedef signed long long int64_t;			// -2147483648 -> 2147483647 // Long
typedef unsigned long long uint64_t; 		// 0 -> 4294967295			 // Unsigned Long


#endif