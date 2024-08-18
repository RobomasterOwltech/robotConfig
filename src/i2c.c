/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
I2C_HandleTypeDef hi2c3;
DMA_HandleTypeDef hdma_i2c2_tx;

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

}
/* I2C2 init function */
void MX_I2C2_Init(void)
{

  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 400000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

}
/* I2C3 init function */
void MX_I2C3_Init(void)
{

  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 400000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration    
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
  else if(i2cHandle->Instance==I2C2)
  {
  /* USER CODE BEGIN I2C2_MspInit 0 */

  /* USER CODE END I2C2_MspInit 0 */
  
    __HAL_RCC_GPIOF_CLK_ENABLE();
    /**I2C2 GPIO Configuration    
    PF0     ------> I2C2_SDA
    PF1     ------> I2C2_SCL 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /* I2C2 clock enable */
    __HAL_RCC_I2C2_CLK_ENABLE();
  
    /* I2C2 DMA Init */
    /* I2C2_TX Init */
    hdma_i2c2_tx.Instance = DMA1_Stream7;
    hdma_i2c2_tx.Init.Channel = DMA_CHANNEL_7;
    hdma_i2c2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_i2c2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_i2c2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_i2c2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_i2c2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_i2c2_tx.Init.Mode = DMA_NORMAL;
    hdma_i2c2_tx.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_i2c2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_i2c2_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(i2cHandle,hdmatx,hdma_i2c2_tx);

  /* USER CODE BEGIN I2C2_MspInit 1 */
    SET_BIT(hi2c2.Instance->CR2, I2C_CR2_DMAEN);

  /* USER CODE END I2C2_MspInit 1 */
  }
  else if(i2cHandle->Instance==I2C3)
  {
  /* USER CODE BEGIN I2C3_MspInit 0 */

  /* USER CODE END I2C3_MspInit 0 */
  
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**I2C3 GPIO Configuration    
    PC9     ------> I2C3_SDA
    PA8     ------> I2C3_SCL 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* I2C3 clock enable */
    __HAL_RCC_I2C3_CLK_ENABLE();
  /* USER CODE BEGIN I2C3_MspInit 1 */

  /* USER CODE END I2C3_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();
  
    /**I2C1 GPIO Configuration    
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }
  else if(i2cHandle->Instance==I2C2)
  {
  /* USER CODE BEGIN I2C2_MspDeInit 0 */

  /* USER CODE END I2C2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C2_CLK_DISABLE();
  
    /**I2C2 GPIO Configuration    
    PF0     ------> I2C2_SDA
    PF1     ------> I2C2_SCL 
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_0|GPIO_PIN_1);

    /* I2C2 DMA DeInit */
    HAL_DMA_DeInit(i2cHandle->hdmatx);
  /* USER CODE BEGIN I2C2_MspDeInit 1 */

  /* USER CODE END I2C2_MspDeInit 1 */
  }
  else if(i2cHandle->Instance==I2C3)
  {
  /* USER CODE BEGIN I2C3_MspDeInit 0 */

  /* USER CODE END I2C3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C3_CLK_DISABLE();
  
    /**I2C3 GPIO Configuration    
    PC9     ------> I2C3_SDA
    PA8     ------> I2C3_SCL 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_8);

  /* USER CODE BEGIN I2C3_MspDeInit 1 */

  /* USER CODE END I2C3_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void bsp_I2C_master_transmit(I2C_TypeDef *I2C, uint16_t I2C_address, uint8_t *data, uint16_t len)
{
    if(I2C == I2C1)
    {
        HAL_I2C_Master_Transmit(&hi2c1, I2C_address, data, len, 100);
    }
    else if(I2C == I2C2)
    {
        HAL_I2C_Master_Transmit(&hi2c2, I2C_address, data, len, 100);
    }
}


void bsp_I2C_reset(I2C_TypeDef *I2C)
{
    I2C_HandleTypeDef *hi2c;
    if(I2C == I2C1)
    {
        hi2c = &hi2c1;
    }
    else if(I2C == I2C2)
    {
        hi2c = &hi2c2;
    }

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_SWRST);
    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_SWRST);
    if (HAL_I2C_Init(hi2c) != HAL_OK)
    {
        Error_Handler();
    }
}



bool_t bsp_I2C_check_ack(I2C_TypeDef *I2C, uint16_t I2C_address)
{
    I2C_HandleTypeDef *hi2c;
    if(I2C == I2C1)
    {
        hi2c = &hi2c1;
    }
    else if(I2C == I2C2)
    {
        hi2c = &hi2c2;
    }

    if((hi2c->Instance->CR2 & I2C_CR2_DMAEN) && ((hi2c->hdmatx != NULL && hi2c->hdmatx->Instance->NDTR != 0) || (hi2c->hdmarx != NULL && hi2c->hdmarx->Instance->NDTR != 0)))
    {
        return I2C_ACK;
    }
    else
    {
        uint16_t timeout = 0;

        timeout = 0;
        while(hi2c->Instance->SR2 & 0x02)
        {
            timeout ++;
            if(timeout > 100)
            {
                SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
                return I2C_NO_ACK;
            }
        }

        CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

        timeout = 0;
        while(!(hi2c->Instance->SR1 & 0x01))
        {
            timeout ++;
            if(timeout > 100)
            {
                SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
                return I2C_NO_ACK;
            }
        }

        hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(I2C_address);

        timeout = 0;
        while(!(hi2c->Instance->SR1 & 0x02))
        {
            timeout ++;
            if(timeout > 500)
            {
                SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
                return I2C_NO_ACK;
            }
        }

        do{
            __IO uint32_t tmpreg = 0x00U;
            tmpreg = hi2c->Instance->SR1;
            tmpreg = hi2c->Instance->SR2;
            UNUSED(tmpreg);
        } while(0);

        timeout = 0;
        while(!(hi2c->Instance->SR1 & 0x80))
        {
            timeout ++;
            if(timeout > 500)
            {
                SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
                return I2C_NO_ACK;
            }
        }

        SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);

        return I2C_ACK;
    }


}



void DMA1_Stream7_IRQHandler(void)
{
    if(DMA1->HISR & (1<<27))
    {
        __HAL_DMA_CLEAR_FLAG(hi2c2.hdmatx, DMA_HISR_TCIF7);
        SET_BIT(hi2c2.Instance->CR1, I2C_CR1_STOP);
    }
}



void I2C2_tx_DMA_init(void)
{

    //disable DMA
    //ʧЧDMA
    __HAL_DMA_DISABLE(hi2c2.hdmatx);
    
    while(hi2c2.hdmatx->Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(hi2c2.hdmatx);
    }
    hi2c2.hdmatx->Instance->PAR = (uint32_t)(&I2C2->DR);
    __HAL_DMA_CLEAR_FLAG(hi2c2.hdmatx, DMA_HISR_TCIF7);
    __HAL_DMA_ENABLE_IT(hi2c2.hdmatx, DMA_IT_TC);



}

void I2C2_tx_DMA_enable(uint32_t tx_buf, uint16_t ndtr)
{
    //disable DMA
    //ʧЧDMA
    __HAL_DMA_DISABLE(hi2c2.hdmatx);

    while(hi2c2.hdmatx->Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(hi2c2.hdmatx);
    }

    __HAL_DMA_CLEAR_FLAG(hi2c2.hdmatx, DMA_HISR_TCIF7);


    hi2c2.hdmatx->Instance->M0AR = tx_buf;
    __HAL_DMA_SET_COUNTER(hi2c2.hdmatx, ndtr);

    __HAL_DMA_ENABLE(hi2c2.hdmatx);

}

HAL_StatusTypeDef I2C_TX_DMA_START(I2C_HandleTypeDef *hi2c, uint16_t DevAddress)
{
    uint16_t timeout = 0;

    if ((hi2c->Instance->CR1 & I2C_CR1_PE) != I2C_CR1_PE)
    {
        hi2c->Instance->CR1 |= I2C_CR1_PE;
    }


    timeout = 0;
    while(hi2c->Instance->SR2 & 0x02)
    {
        timeout ++;
        if(timeout > 100)
        {
            SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
            return HAL_BUSY;
        }
    }


    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_POS);

    SET_BIT(hi2c->Instance->CR1, I2C_CR1_START);

    timeout = 0;
    while(!(hi2c->Instance->SR1 & 0x01))
    {
        timeout ++;
        if(timeout > 100)
        {
            SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
            return HAL_ERROR;
        }
    }


    hi2c->Instance->DR = I2C_7BIT_ADD_WRITE(DevAddress);


    timeout = 0;
    while(!(hi2c->Instance->SR1 & 0x02))
    {
        timeout ++;
        if(timeout > 500)
        {
            SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
            return HAL_ERROR;
        }
    }

    do{
        __IO uint32_t tmpreg = 0x00U;
        tmpreg = hi2c->Instance->SR1;
        tmpreg = hi2c->Instance->SR2;
        UNUSED(tmpreg);
    } while(0);



    timeout = 0;
    while(!(hi2c->Instance->SR1 & 0x80))
    {
        timeout ++;
        if(timeout > 500)
        {
            SET_BIT(hi2c->Instance->CR1, I2C_CR1_STOP);
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}
void I2C2_DMA_transmit(uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    if( I2C_TX_DMA_START(&hi2c2, DevAddress) == HAL_OK)
    {
        I2C2_tx_DMA_enable((uint32_t)pData, Size);
    }
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
