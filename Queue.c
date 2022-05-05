/*
 * Queue.c
 *
 *  Created on: Mar 19, 2022
 *      Author: Diego Roa
 */

#include "Queue.h"
#include "Portable.h"

unsigned short Queue_init (T_QUEUE_HANDLER_PTR Queue)
{
    unsigned short Res= QUEUE_ERR_NULL;
    if (Queue)
    {
        Queue -> count = 0;
        Queue -> head = NULL;
        Queue -> tail = NULL;
        Res = QUEUE_OK;
    }
    return Res;
}

unsigned short Queue_getcount (T_QUEUE_HANDLER_PTR Queue)
{
    if(Queue)
    {
        return Queue -> count;
    }
    return 0;
}

u16 Queue_enqueue (T_QUEUE_HANDLER_PTR Queue, T_QUEUE_ELEMENT_PTR element)
{
    u16 Res= QUEUE_ERR_NULL;
    if((Queue)&&(element))
    {
        element -> Next = NULL;
        if(Queue -> tail)
        {
        	Queue-> tail -> Next = element;
            Queue -> tail = element;
            Queue -> count++;
        }
        else
        {
            Queue -> head = element;
            Queue -> tail = element;
            Queue -> count = 1;
        }
        Res = QUEUE_OK;
    }
    return Res;
}

u16 Queue_dequeue (T_QUEUE_HANDLER_PTR Queue, T_QUEUE_ELEMENT_PTR* element)
{
    u16 Res = QUEUE_ERR_NULL;
    if((Queue) && (element))
    {
    	if(Queue->head != NULL)
    	{
    	Res = QUEUE_OK;
    	*element = Queue->head;
    	Queue->head = (*element)->Next;
    	if(Queue->head == NULL)
    	{
    	Queue->tail = NULL;
    	Queue->count = 0;
    	}
    	else
    	{
    	Queue->count--;
    	}
    	}
    	}
    	return Res;
}

u16 Queue_Copy(T_QUEUE_HANDLER_PTR Source, T_QUEUE_HANDLER_PTR Destination)
{
u16 Res = QUEUE_ERR_NULL;
if((Source != NULL) && (Destination != NULL))
{
Portable_DisableInterrupts();
Destination->count = Source->count;
Destination->head = Source->head;
Destination->tail = Source->tail;
Res = QUEUE_OK;
Portable_EnableInterrupts();
}
return Res;
}


