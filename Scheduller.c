/*
 * Scheduller.c
 *
 *  Created on: Mar 19, 2022
 *      Author: 57321
 */

#include "Task.h"
#include "Queue.h"
#include "Scheduller.h"
#include "RTOS.h"

T_QUEUE_HANDLER ReadyTaskList[RTOS_SYSTEM_PRIORITIES];
extern T_TCB IdleTaskHandler;
u16 Scheduller_Init(void)
{
    u16 Res;
    u16 Count;
    for(Count =0; Count < RTOS_SYSTEM_PRIORITIES; Count ++)
    {
        Res= Queue_init(&ReadyTaskList[Count]);
        if(Res!=SCHEDULLER_OK)
        {
            break;
        }
    }
    return Res;
}

u16 Scheduller_SetTaskToReadyQueue(T_TCB_PTR Task)
{
	u16 Res= SCHEDULLER_ERROR_NULL_PARAM;
	if(Task!= NULL)
	{
		Task ->Status = READY;
		if(Task->TaskPriority < RTOS_SYSTEM_PRIORITIES) //Verificar rango de la tarea
		{
			Task->TaskQueueElement.Data = Task; //Inicilaiza cola de la tarea
			Task->TaskQueueElement.Next = NULL;
			Res = Queue_enqueue(&ReadyTaskList[Task->TaskPriority], &Task->TaskQueueElement); //Encola
		}
		else
		Res= SCHEDULLER_ERROR_PARAM_OUT_OF_RANGE;
	}
	return Res;
}

u16 Scheduller_Cooperative(u16 ActualTaskSP)
{
	u16 Res;
	u16 Count;
	T_TCB_PTR Task = NULL;
	T_QUEUE_ELEMENT_PTR Element = NULL;
	Task = Task_GetActualTask();
	if (Task != NULL)
	{
		if(ActualTaskSP != 0)
		{
			Task->TaskActualStack = ActualTaskSP;
		}
		
		if (Task!= &IdleTaskHandler)
		{
			if(Task_CheckStack(Task) == TASK_OK)
			{
				if(Task->Status == RUNNING)
				{
					Res = Scheduller_SetTaskToReadyQueue(Task);
				}
			}
			else
			{
				Task->Status = BLOCKED;
			}
		}
		else
		{
			Task->Status = READY;
		}
	}
	Task = NULL;
	for(Count = 0; Count < RTOS_SYSTEM_PRIORITIES; Count++)
	{
		if(Queue_getcount(&ReadyTaskList[Count]) > 0)
		{
			Res = Queue_dequeue(&ReadyTaskList[Count], &Element);
			if(Res ==QUEUE_OK)
			{
				if(Element != NULL)
				{
					Task = Element->Data;
					break;
				}
			}
		}
	}
	if(Task == NULL)
	{
		Task = &IdleTaskHandler;
	}
	Task->Status = RUNNING;
	Task_SetActualTask(Task);
	return Task->TaskActualStack;
}

