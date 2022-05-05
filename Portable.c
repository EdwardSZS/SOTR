/*
 * Portable.c
 *
 *  Created on: Mar 19, 2022
 *      Author: 57321
 */
#include "Portable.h"
#include "Task.h"
#include "IO_Map.h"
//#include "LED1.h"
//#include "LED_2.h"
u8 *ActualStack;
u16 CurrentStackPtr;      //Direccion de memoria a almacenar H-X
u8  CriticalNesting = 0;
u16 CountTick=0;
#define Portable_SaveContext()  asm (TSX);\
                                asm (STHX CurrentStackPtr) //Instrucciones para guardar contexto
#define Portable_Restore         asm (LDHX CurrentStackPtr);\
                                asm (TXS)

extern u16 Scheduller_Cooperative(u16 ActualTaskSP);
extern v Task_DecrementTimer(v);

pu8 Portable_InitTaskContext(pu8 Stack, TaskFunction Function, void * Param)
{
	if((!Stack) || (!Function))
	{
		return NULL;
	}
	Stack--;
	*Stack = (u8)(((u16)Function) & 0x00FF); //Asigna PROGRAM COUNTER LOW
	Stack--;
	*Stack = (u8)((((u16)Function) >> 8) & 0x00FF); //Asigna PROGRAM COUNTER HIGH
	Stack--;
	*Stack = (u8)((u16)Param & 0x00FF); //Asigancion X
	Stack--;
	*Stack = 0; //Asignacion de A
	Stack--;
	*Stack = 0; //Asignacion de CCR
	Stack--;
	*Stack = (u8)(((u16)Param) >> 8) & 0x00FF; //Asignacion de H
	Stack--;
	*Stack = 1; //Asignacion del Critical Nesting
	return Stack;
}

//interrupcion de software
__interrupt void ISR_SoftwareInterrupt(void)
{
	//LED1_SetVal();
	CriticalNesting++;
	asm{
		LDA		CriticalNesting
		PSHA //Enviando al stack criticalnesting
		TSX
		STHX	CurrentStackPtr
	}
	CurrentStackPtr = Scheduller_Cooperative(CurrentStackPtr); //Retorna el Stack pointer de la tarea a ejecutar
	asm{
		LDHX	CurrentStackPtr
		TXS
		PULA
		STA		CriticalNesting 
	} 
	CriticalNesting--;
	//LED1_ClrVal();
}

//Interrupcion 
__interrupt void ISR_TimerInterrupt(void)
{ //inicializar un  timer
	//LED_2_SetVal();
	RTC_SC1 |= 0x80U;
	
	CriticalNesting++;
	asm{
		LDA		CriticalNesting
		PSHA //Enviando al stack criticalnesting
		TSX
		STHX	CurrentStackPtr
	}
	Task_DecrementTimer();
	CountTick++;
	CurrentStackPtr = Scheduller_Cooperative(CurrentStackPtr); //Retorna el Stack pointer de la tarea a ejecutar
	asm{
		LDHX	CurrentStackPtr
		TXS
		PULA
		STA		CriticalNesting 
	}
	CriticalNesting--;
	//LED_2_ClrVal();
	IPC_SC_PULIPM = 1U;
	//salida del Timer
}

v Portable_InitTickRTC(v)
{
	RTC_SC2 = 0x07;
	//RTC_MOD = 0x013F;
	RTC_MODL = 0x1B;
	RTC_MODH = 0x03;
	//RTC_MOD = RTC_MOD;
	RTC_SC1 = 0xC0;
	RTC_SC2=  0xC6;
}

v Portable_DisableInterrupts(v)
{
	asm(SEI);
	CriticalNesting++;
}


v Portable_EnableInterrupts(v)
{
	if(CriticalNesting)
	 {
	   CriticalNesting--;
	  if(!CriticalNesting)
	  {
	   asm(CLI);
	  }
     }
}
v Portable_RestoreManualContext(u16 Stack)
{
	CurrentStackPtr = Stack;
	asm{
		LDHX		 CurrentStackPtr
		TXS
		PULA
		STA			CriticalNesting
		PULH
		RTI
	}
}
