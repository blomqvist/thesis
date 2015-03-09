/*
 * pc_typedefs.h
 *
 *  Created on: 5 mar 2015
 *      Author: bt4268
 */

#ifndef PC_TYPEDEFS_H_
#define PC_TYPEDEFS_H_

#define FALSE 0
#define TRUE  1
#define WHAT  2

// Variable sizes for PC
typedef unsigned char   UByte;      //!< 1 Byte   0..255
typedef char            SByte;      //!< 1 Byte   -128..127
typedef unsigned short  UWord;      //!< 2 Bytes  0..65535
typedef signed short    SWord;      //!< 2 Bytes  -32768..32767
typedef unsigned int    ULong;      //!< 4 Bytes  0..4294967295
typedef signed int      SLong;      //!< 4 Bytes  -2147483648..2147483647
typedef float           Float;      //!< 4 Bytes  1,176E-38..3,402E+38
typedef double          Double;     //!< 8 Bytes  2,225E-308..1,797E+308
typedef unsigned char   Bool;       //!< 1 Bit    0..1

#endif /* PC_TYPEDEFS_H_ */
