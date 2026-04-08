



#ifndef CHECKSUM_H
#define CHECKSUM_H
#include <stdint.h>




typedef unsigned char UCHAR;
typedef uint16_t USHORT;
USHORT CalcCRC( UCHAR * pucFrame, USHORT usLen );

#endif /*End of CHECKSUM_H*/