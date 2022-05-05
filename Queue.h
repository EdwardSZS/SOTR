/*
 * Queue.h
 *
 *  Created on: Mar 19, 2022
 *      Author: 57321
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#define QUEUE_ERR_NULL 0x0FF
#define QUEUE_ERR_EMPTY 0X400
#define QUEUE_OK 0

#include "AppTypes.h"

typedef struct Queue_element
{
    void *Data;
    struct Queue_element *Next;
}T_QUEUE_ELEMENT, *T_QUEUE_ELEMENT_PTR;

typedef struct {
    unsigned short count;
    T_QUEUE_ELEMENT_PTR head;
    T_QUEUE_ELEMENT_PTR tail;
}T_QUEUE_HANDLER, *T_QUEUE_HANDLER_PTR;

u16 Queue_init (T_QUEUE_HANDLER_PTR Queue);
u16 Queue_getcount (T_QUEUE_HANDLER_PTR Queue);
u16 Queue_enqueue (T_QUEUE_HANDLER_PTR Queue, T_QUEUE_ELEMENT_PTR element);
u16 Queue_dequeue (T_QUEUE_HANDLER_PTR Queue, T_QUEUE_ELEMENT_PTR* element);
u16 Queue_Copy(T_QUEUE_HANDLER_PTR Source, T_QUEUE_HANDLER_PTR Destination );



#endif /* QUEUE_H_ */
