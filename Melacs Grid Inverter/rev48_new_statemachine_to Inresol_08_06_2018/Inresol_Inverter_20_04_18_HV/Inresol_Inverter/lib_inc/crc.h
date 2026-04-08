/*
 *  File name: CRC.h
 *
 *  Description: CRC function declarations
 *
 *  Author: Unknown
 *
 */

#ifndef CRC_H
#define CRC_H

#define CRC32_INIT_VALUE	0xFFFFFFFFL
#define CRC32_XOR_VALUE		0xFFFFFFFFL

extern uint32_t crc32(uint32_t crc, const uint8_t* buf, int16_t len);
extern void CRC32_InitChecksum( uint32_t *crcvalue );
extern void CRC32_Update( uint32_t *crcvalue, const uint8_t data );
extern void CRC32_UpdateChecksum( uint32_t *crcvalue, const void *data, int16_t length );
extern void CRC32_FinishChecksum( uint32_t *crcvalue );
extern uint32_t CRC32_BlockChecksum( const void *data, int16_t length );

#endif // CRC_H
