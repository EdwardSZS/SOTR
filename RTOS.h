#ifndef RTOS_H
#define RTOS_H

#include "AppTypes.h"

#define RTOS_MAX_PRIORITIES         0
#define RTOS_MIN_PRIORITY           RTOS_SYSTEM_PRIORITIES - 1
#define RTOS_SYSTEM_PRIORITIES      8

#define RTOS_MIN_STACK_SIZE         64
#define RTOS_STACK_CHECK_BYTE   	0x5C
#define RTOS_STACK_CHECK_COUNT		8
#define RTOS_OK						0
#define RTOS_IDLE_TASK_PRIORITY     RTOS_SYSTEM_PRIORITIES
#define RTOS_IDLE_TASK_STACK_SIZE   RTOS_MIN_STACK_SIZE
#define RTOS_IDLE_TASK_ID   		255
#define RTOS_IDLE_TASK_NAME   		"Idle Task"

u16 RTOS_Init(v); //Funcion que inicialize RTOS
u16 RTOS_Start(v);//Funcion que arranque RTOS

#endif
