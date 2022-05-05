/*
 * AppTypes.h
 *
 *  Created on: Mar 19, 2022
 *      Author: Diego Roa
 */

#ifndef APPTYPES_H_
#define APPTYPES_H_

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef FALSE
#define FALSE 0x02
#endif

#ifndef TRUE
#define TRUE 0x01
#endif

#define BASE_ERROR_UNKNOW					0x500
#define BASE_ERROR_NULL_PARAM				0x501
#define BASE_ERROR_EMPTY					0x502
#define BASE_ERROR_PARAM_OUT_OF_RANGE		0x503

typedef signed char s8;
typedef unsigned char u8;
typedef signed char* ps8;
typedef unsigned char* pu8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed short* ps16;
typedef unsigned short* pu16;
typedef signed long s32;
typedef unsigned long u32;
typedef signed long* ps32;
typedef unsigned long* pu32;
typedef float f;
typedef float* pf;
typedef double d;
typedef double* pd;
typedef void v;
typedef void* pv;


#endif /* APPTYPES_H_ */
