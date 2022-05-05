/*
 * Task.h
 *
 *  Created on: Mar 19, 2022
 *      Author: 57321
 */

#ifndef TASK_H_
#define TASK_H_

#include "AppTypes.h"
#include "Queue.h"
#include "RTOS.h"

#define TASK_OK             				0
#define TASK_BASE_ERROR						0x600
#define TASK_ERROR_OVER_FLOW				0x700

#define TASK_ERROR_UNKNOW                   TASK_BASE_ERROR | BASE_ERROR_UNKNOW
#define TASK_ERROR_NULL_PARAM               TASK_BASE_ERROR | BASE_ERROR_NULL_PARAM
#define TASK_ERROR_EMPTY                    TASK_BASE_ERROR | BASE_ERROR_EMPTY
#define TASK_ERROR_PARAM_OUT_OF_RANGE       TASK_BASE_ERROR | BASE_ERROR_PARAM_OUT_OF_RANGE


#define TIMEROFF16        0xFFFF //debe ser así pues son 16 bits por eso FFFF y lo otro es para que al poner 500 en time, este llegaba  a 255 y quedaba pegado

typedef void(*TaskFunction)(void * Param);

typedef enum 
{
    RUNNING =0,
    READY,
    BLOCKED
}TaskStatus, *TaskStatus_PTR;

typedef struct //Estructura TCB o Tarea
{
    unsigned short Id;
    char * TaskName; //Apuntador al nombre de la tarea
    void * TaskParam;
    u8 TaskStackOverflow;
    TaskStatus Status;
    unsigned char TaskPriority;
    TaskFunction TaskCallback;
    T_QUEUE_ELEMENT TaskQueueElement;
    pu8 TaskStack;//Apuntador a vector que se designa en RAM ¿DONDE ESTA EL VECTOR?
    u16 TaskActualStack;//Apuntador Stack pointer
    u16 TaskStackSize;
    u16 TaskSleepTime;
}T_TCB, *T_TCB_PTR;

T_TCB_PTR Task_GetActualTask(void);
v Task_SetActualTask(T_TCB_PTR Task);
u16 Task_Create(T_TCB_PTR TaskHandler, u16 Id, char * Name, u8 Priority, pu8 Stack, u16 StackSize, TaskFunction Function, v *Param);
u16 Task_CheckStack(T_TCB_PTR TaskHandler);
u16 Task_Sleep(u16 SleepTicks);
u16 Task_Init(v);
#endif
