/**
 ******************************************************************************
 * @file    can.c
 * @brief   This file provides code for the configuration
 *          of the CAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "can.h"

CAN_HandleTypeDef hcan;
CAN_FilterTypeDef filterCanBus;

CAN_TxHeaderTypeDef TxHeaderCan;
CAN_RxHeaderTypeDef RxHeaderCan;

uint8_t TxDataCan[8];
uint8_t RxDataCan[8];

uint32_t TxMailboxCan;

/* CAN init function */
void MX_CAN_Init(void) {
    hcan.Instance = CAN;
    hcan.Init.Prescaler = 16;
    hcan.Init.Mode = CAN_MODE_NORMAL;
    hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan.Init.TimeSeg1 = CAN_BS1_1TQ;
    hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
    hcan.Init.TimeTriggeredMode = DISABLE;
    hcan.Init.AutoBusOff = DISABLE;
    hcan.Init.AutoWakeUp = DISABLE;
    hcan.Init.AutoRetransmission = DISABLE;
    hcan.Init.ReceiveFifoLocked = DISABLE;
    hcan.Init.TransmitFifoPriority = DISABLE;
    if (HAL_CAN_Init(&hcan) != HAL_OK) {
        Error_Handler();
    }
}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (canHandle->Instance == CAN) {
        /* CAN clock enable */
        __HAL_RCC_CAN1_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**CAN GPIO Configuration
        PB8     ------> CAN_RX
        PB9     ------> CAN_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_CAN;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        // Activate Interrups
        HAL_CAN_ActivateNotification(&hcan, );
        /*
        The notifications I believe can com in handy are:
        CAN_IT_TX_MAILBOX_EMPTY - Transmit mailbox empty interrupt

        CAN_IT_RX_FIFO0_MSG_PENDING - FIFO 0 message pending interrupt
        CAN_IT_RX_FIFO0_FULL - FIFO 0 full interrupt
        CAN_IT_RX_FIFO0_OVERRUN - FIFO 0 overrun interrupt

        CAN_IT_RX_FIFO1_MSG_PENDING - FIFO 1 message pending interrupt
        CAN_IT_RX_FIFO1_FULL - FIFO 1 full interrupt
        CAN_IT_RX_FIFO1_OVERRUN - FIFO 1 overrun interrupt

        CAN_IT_WAKEUP - Wake-up interrupt
        CAN_IT_SLEEP_ACK - Sleep acknowledge interrupt

        CAN_IT_ERROR_WARNING - Error warning interrupt
        CAN_IT_ERROR_PASSIVE - Error passive interrupt

        CAN_IT_BUSOFF - Bus-off interrupt
        CAN_IT_LAST_ERROR_CODE - Last error code interrupt
        CAN_IT_ERROR Error Interrupt
        */

        -- -- --Configure the CAN interrupt priority using HAL_NVIC_SetPriority()
                  Enable the CAN IRQ handler using HAL_NVIC_EnableIRQ() In CAN IRQ handler,
            call HAL_CAN_IRQHandler

                // Set priority
                HAL_NVIC_SetPriority(EXTI0_IRQn, 3, 0);
        // Enable priority
        HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle) {
    if (canHandle->Instance == CAN) {
        /* Peripheral clock disable */
        __HAL_RCC_CAN1_CLK_DISABLE();

        /**CAN GPIO Configuration
        PB8     ------> CAN_RX
        PB9     ------> CAN_TX
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);
    }
}

// Filter
// TODO: Configure CAN2
void CAN_FILTER_Init(void) {
    // Since this is a filter, we can choose to
    // only accept certain messages.
    // We can decide which ones based on an ID number
    // or a mask, kinda CIDR block.
    // Since we want to receive all of them, we assign them values
    // filterCanBus.FilterIdHigh = 0x0000;
    // filterCanBus.FilterIdLow = 0x0000;
    filterCanBus.FilterMaskIdHigh = 0x0000;
    filterCanBus.FilterMaskIdLow = 0x0000;
    filterCanBus.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    // This could be useful to group even more from the allowed messages
    // I imagine it to be a "FilterId"
    filterCanBus.FilterBank = 0;
    filterCanBus.FilterMode = CAN_FILTERMODE_IDMASK;
    // We should not be receiving 29 bits ids
    filterCanBus.FilterScale = CAN_FILTERSCALE_16BIT;
    filterCanBus.FilterActivation = CAN_FILTER_ENABLE;
    HAL_CAN_ConfigFilter(&hcan, &filterCanBus);

    // To be done at task
    // HAL_CAN_Start(&hcan);
    // HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}