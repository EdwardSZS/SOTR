/*
 * Task.c
 *
 *  Created on: Mar 19, 2022
 *      Author: 57321
 */
#include "Queue.h"
#include "Portable.h"
#include "Scheduller.h"
#include "Task.h"

v Task_DecrementTimer(v);

T_TCB_PTR ActualTask = NULL;
T_QUEUE_HANDLER TimeBlockedTaskQueue;

T_TCB_PTR Task_GetActualTask(void)
{
    return ActualTask;
}
v Task_SetActualTask(T_TCB_PTR Task)
{
	ActualTask=Task;

}

u16 Task_Init(v)
{
	return Queue_init(&TimeBlockedTaskQueue);
}

u16 Task_Create(T_TCB_PTR TaskHandler, u16 Id, char * Name, u8 Priority, pu8 Stack, u16 StackSize, TaskFunction Function, v * Param )
{
	u16 Count = 0;
    u16 Res = TASK_ERROR_NULL_PARAM;
    if((TaskHandler != NULL) && (Stack != NULL) &&(StackSize > 0) && (Function != NULL))
    {
        Res = TASK_ERROR_PARAM_OUT_OF_RANGE;
        if(StackSize >= RTOS_MIN_STACK_SIZE) 
        {
            Res= TASK_OK;
            if(Priority >= RTOS_MIN_PRIORITY)
            {
                Priority = RTOS_MIN_PRIORITY;
            }
            TaskHandler->Id = Id;
            TaskHandler->TaskName= Name;
            TaskHandler->TaskPriority= Priority;
            TaskHandler->TaskParam = Param;
            TaskHandler->TaskStackOverflow = FALSE;
            TaskHandler->TaskCallback = Function;
            TaskHandler->TaskStack = Stack;
            TaskHandler->TaskStackSize = StackSize;
            TaskHandler->TaskSleepTime = TIMEROFF16;
            for(Count = 0; Count <StackSize;Count++)
            {
            	Stack[Count] = RTOS_STACK_CHECK_BYTE;
            }
            TaskHandler->TaskActualStack=(u16)Portable_InitTaskContext(&Stack[StackSize], Function, Param);
            Res = Scheduller_SetTaskToReadyQueue(TaskHandler);
        }
    }
    return Res;
}

u16 Task_CheckStack(T_TCB_PTR TaskHandler)
{
	u16 Count;
	u16 Res= TASK_ERROR_NULL_PARAM;
	if(TaskHandler != NULL)
	{
		Res=TASK_OK;
		for(Count = 0; Count< RTOS_STACK_CHECK_COUNT; Count++)
		{
			if(TaskHandler->TaskStack[Count] != RTOS_STACK_CHECK_BYTE)
			{
				TaskHandler->TaskStackOverflow = TRUE;
				Res= TASK_ERROR_OVER_FLOW;
			}
		}
	}
	return Res;
}

u16 Task_Sleep(u16 SleepTicks)
{
	u8 CallScheduller = FALSE;
	u16 Res = TASK_OK;
	T_TCB_PTR Task;
	if(SleepTicks)
	{
		Portable_DisableInterrupts();
		if(SleepTicks == TIMEROFF16)
		{
			SleepTicks--;
		}
		Task = Task_GetActualTask();
		if(Task != NULL)
		{
			Task ->TaskSleepTime = SleepTicks;
			Task ->Status = BLOCKED;
			Task ->TaskQueueElement.Data = Task;
			Task ->TaskQueueElement.Next = NULL;
			Res = Queue_enqueue(&TimeBlockedTaskQueue, &Task -> TaskQueueElement);
			if(Res == QUEUE_OK)
			{
				CallScheduller = TRUE;
			}
		}
		Portable_EnableInterrupts();
		if(CallScheduller)
		{
			Portable_SoftwareInterrupt(); //punto de retorno
		}
	}
	return Res;
}


v Task_DecrementTimer(v)
{
	T_TCB_PTR Task;
	T_QUEUE_ELEMENT_PTR Element;
	T_QUEUE_HANDLER TempQueue;
	if(Queue_init(&TempQueue)== QUEUE_OK)
	{
		while(Queue_dequeue(&TimeBlockedTaskQueue,&Element)==QUEUE_OK)//cambio 1 faltaba el QUEUE_OK
		{
			if(Element != NULL)
			{
				if(Element->Data != NULL)
				{
					Task =(T_TCB_PTR)Element->Data;
					if(Task->TaskSleepTime != TIMEROFF16)
					{
						Task->TaskSleepTime--;
						if(Task -> TaskSleepTime == 0)
						{
							Task->TaskSleepTime = TIMEROFF16;
							(v)Scheduller_SetTaskToReadyQueue(Task);
						}
						else
						{
							(void)Queue_enqueue(&TempQueue, Element);
						}
					}
					else
					{
						(v)Scheduller_SetTaskToReadyQueue(Task);
					}
				}
			}
		}
		(v)Queue_Copy(&TempQueue, &TimeBlockedTaskQueue);
	}
}

