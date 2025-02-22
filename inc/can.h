/**
 ******************************************************************************
 * @file    can.h
 * @brief   This file contains all the function prototypes for
 *          the can.c file
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "robotPins.h"

extern CAN_HandleTypeDef hcan;
extern CAN_FilterTypeDef filterCanBus;

extern CAN_TxHeaderTypeDef TxHeaderCan;
extern CAN_RxHeaderTypeDef RxHeaderCan;

extern uint32_t TxMailboxCan;

void MX_CAN_Init(void);

// TODO: Validate they are not being overwritten

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle);
void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle);
void CAN_FILTER_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */
