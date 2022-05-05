/*
 * Portable.h
 *
 *  Created on: Mar 19, 2022
 *      Author: 57321
 */

#ifndef PORTABLE_H_
#define PORTABLE_H_

#include "AppTypes.h"
#include "Task.h"

#define Portable_SoftwareInterrupt()	asm(SWI)

typedef void (*TaskFunction)(void * Param);
		
pu8 Portable_InitTaskContext(pu8 Stack, TaskFunction Function, void * Param); //Crea contexto inicial de cada tarea.
v Portable_InitTickRTC(v);
v Portable_DisableInterrupts(v);
v Portable_EnableInterrupts(v);
v Portable_RestoreManualContext(u16 Stack);
v Portable_EnableInterrupts(v);
__interrupt void ISR_SoftwareInterrupt(void);
__interrupt void ISR_TimerInterrupt(void);

#endif /* PORTABLE_H_ */
