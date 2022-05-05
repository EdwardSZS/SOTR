#include <hidef.h> /* for EnableInterrupts macro */
//#include "derivative.h" /* include peripheral declarations */

#include "Cpu.h"
#include "Events.h"
#include "LED1.h"
#include "LED_2.h"
#include "Tick.h"
#include "LED_3.h"
#include "LED_4.h"
#include "BUTTON.h"
#include "LED_BUTTON.h"
#include "ADC1.h"
#include "PWM1.h"
#include "LED2H.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "AppTypes.h"
#include "Task.h"
#include "Queue.h"
#include "RTOS.h"


T_TCB Tarea1;
T_TCB Tarea2;
T_TCB Tarea3;
T_TCB Tarea4;
u8 Tarea1Stack[RTOS_MIN_STACK_SIZE];
u8 Tarea2Stack[RTOS_MIN_STACK_SIZE];
u8 Tarea3Stack[RTOS_MIN_STACK_SIZE];
u8 Tarea4Stack[RTOS_MIN_STACK_SIZE];
u8 Potenciometro;

void FuncionTarea1(void *Param)
{
	u16 Time =(u16)Param;
	u16 Count;
	for(;;)
	{
		(v)Task_Sleep(Time);
		//for(Count = Time; Count > 0; Coun --)
		//{}
		//LED1_NegVal();
		//LED_2_SetVal();
		//LED_3_NegVal();
	}
}

void FuncionTarea2(void *Param)
{
	u16 Time =(u16)Param;
	u16 Count;
	for(;;)
	{
		(v)Task_Sleep(Time);
		//for(Count = Time; Count > 0; Coun --)
		//{}
		//LED1_NegVal();
		//LED_2_SetVal();
		//LED_4_NegVal();
		LED2H_NegVal();
	}
}

void FuncionTarea3(void *Param)
{
	u16 Time =(u16)Param;
	u16 Count;
	for(;;)
	{
		(v)Task_Sleep(Time);
		if(BUTTON_GetVal())
		{
			LED_BUTTON_ClrVal();
		}
		else
		{
			LED_BUTTON_SetVal();
		}
	}
}

void FuncionTarea4(void *Param)
{
	u16 Time =(u16)Param;
	u16 Count;
	
	for(;;)
	{
		(v)Task_Sleep(Time);
		(v)ADC1_Measure(TRUE);
		(v)ADC1_GetValue8(&Potenciometro);
		(v)PWM1_SetRatio8(Potenciometro);
		
	}
}

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  //EnableInterrupts;
  /* include your code here */
  (v)RTOS_Init();
  
  (v)Task_Create(&Tarea1, 1, "Tarea 1", 3, Tarea1Stack, RTOS_MIN_STACK_SIZE, FuncionTarea1, (pv) 1 );
  (v)Task_Create(&Tarea2, 2, "Tarea 2", 3, Tarea2Stack, RTOS_MIN_STACK_SIZE, FuncionTarea1, (pv) 2 );
  (v)Task_Create(&Tarea3, 3, "Tarea 3", 3, Tarea3Stack, RTOS_MIN_STACK_SIZE, FuncionTarea1, (pv) 3 );
  (v)Task_Create(&Tarea4, 4, "Tarea 4", 3, Tarea4Stack, RTOS_MIN_STACK_SIZE, FuncionTarea1, (pv) 4 );
  
  (v)RTOS_Start();
  
  

  for(;;) {
    __RESET_WATCHDOG();	/* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
  
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/
