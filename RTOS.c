/*
 * RTOS.c
 *
 *  Created on: Mar 19, 2022
 *      Author: 57321
 */

#include "RTOS.h"
#include "Task.h"
#include "Scheduller.h"
#include "Portable.h"

v RTOS_IdleTask (pv Param);
u32 Count=0;
T_TCB IdleTaskHandler;
u8 IdleTaskStack[RTOS_IDLE_TASK_STACK_SIZE];
u16 RTOS_CreateIdleTask(v);

u16 RTOS_Init(v)
{
	u16 Res;
	Res = Task_Init();
	if(Res == TASK_OK)
    {
		Res = Scheduller_Init();
    }
	return Res;
}

u16 RTOS_Start(v)
{
    u16 Res;
    u16 FirstTaskSP;
    Res = RTOS_CreateIdleTask(); //Crear tarea inactiva
    if (Res)
    {
        return Res;
    }
    
    FirstTaskSP = Scheduller_Cooperative(0);
    Portable_InitTickRTC();
    Portable_RestoreManualContext(FirstTaskSP);
    return Res;
}

v RTOS_IdleTask (pv Param)
{ 
	for(;;)
	{
		Count++;
	}
}
//Función que crea la tarea inactiva
u16 RTOS_CreateIdleTask(v)
{
	u16 Count;
	u16 Res= TASK_ERROR_NULL_PARAM;
	if((IdleTaskStack != NULL) &&(RTOS_IDLE_TASK_STACK_SIZE > 0))
	    {
	        Res =TASK_ERROR_PARAM_OUT_OF_RANGE;
	        if(RTOS_IDLE_TASK_STACK_SIZE >= RTOS_MIN_STACK_SIZE) 
	        {
	            Res= TASK_OK;
	            IdleTaskHandler.Id = RTOS_IDLE_TASK_ID;
	            IdleTaskHandler.TaskName= RTOS_IDLE_TASK_NAME;
	            IdleTaskHandler.TaskParam = NULL;
	            IdleTaskHandler.TaskStackOverflow = FALSE;
	            IdleTaskHandler.TaskCallback = RTOS_IdleTask;
	            IdleTaskHandler.TaskStack = IdleTaskStack;
	            IdleTaskHandler.TaskStackSize = RTOS_IDLE_TASK_STACK_SIZE;
	            IdleTaskHandler.TaskSleepTime = TIMEROFF16;
	            for(Count = 0; Count <RTOS_IDLE_TASK_STACK_SIZE;Count++)
	             {
	            	IdleTaskStack[Count] = RTOS_STACK_CHECK_BYTE;
	             }
	            IdleTaskHandler.TaskActualStack = (u16)Portable_InitTaskContext(&IdleTaskStack[RTOS_IDLE_TASK_STACK_SIZE ], IdleTaskHandler.TaskCallback, IdleTaskHandler.TaskParam);
	            Res = RTOS_OK;
	           }
       }
	return Res;
//T_QUEUE_HANDLER ReadyTaskList[RTOS_SYSTEM_PRIORITIES];//Vector de colas con las tareas listas para ejecutarse
}

