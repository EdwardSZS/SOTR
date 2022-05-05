/*
 * Scheduller.h
 *
 *  Created on: Mar 19, 2022
 *      Author: 57321
 */

#ifndef SCHEDULLER_H_
#define SCHEDULLER_H_

#include "AppTypes.h"

#define SCHEDULLER_OK			       0
#define SCHEDULLER_BASE_ERROR		   0x700

#define SCHEDULLER_ERROR_NULL_PARAM         SCHEDULLER_BASE_ERROR|BASE_ERROR_NULL_PARAM
#define SCHEDULLER_ERROR_PARAM_OUT_OF_RANGE    SCHEDULLER_BASE_ERROR | BASE_ERROR_PARAM_OUT_OF_RANGE

u16 Scheduller_Cooperative(u16 ActualTaskSP);
u16 Scheduller_SetTaskToReadyQueue(T_TCB_PTR Task);
u16 Scheduller_Init(v);


#endif /* SCHEDULLER_H_ */
