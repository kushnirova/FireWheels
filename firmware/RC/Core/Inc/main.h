/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_0
#define LED_GPIO_Port GPIOA
#define IRQ_Pin GPIO_PIN_0
#define IRQ_GPIO_Port GPIOB
#define IRQ_EXTI_IRQn EXTI0_IRQn
#define SPI1_CSN_Pin GPIO_PIN_1
#define SPI1_CSN_GPIO_Port GPIOB
#define RAB_Pin GPIO_PIN_10
#define RAB_GPIO_Port GPIOB
#define LAB_Pin GPIO_PIN_11
#define LAB_GPIO_Port GPIOB
#define CE_Pin GPIO_PIN_12
#define CE_GPIO_Port GPIOB
#define BA_Pin GPIO_PIN_9
#define BA_GPIO_Port GPIOA
#define BB_Pin GPIO_PIN_10
#define BB_GPIO_Port GPIOA
#define BY_Pin GPIO_PIN_11
#define BY_GPIO_Port GPIOA
#define BX_Pin GPIO_PIN_12
#define BX_GPIO_Port GPIOA
#define DPD_Pin GPIO_PIN_15
#define DPD_GPIO_Port GPIOA
#define DPR_Pin GPIO_PIN_3
#define DPR_GPIO_Port GPIOB
#define DPL_Pin GPIO_PIN_4
#define DPL_GPIO_Port GPIOB
#define DPU_Pin GPIO_PIN_5
#define DPU_GPIO_Port GPIOB
#define RBMPR_Pin GPIO_PIN_6
#define RBMPR_GPIO_Port GPIOB
#define RTR_Pin GPIO_PIN_7
#define RTR_GPIO_Port GPIOB
#define LBMPR_Pin GPIO_PIN_8
#define LBMPR_GPIO_Port GPIOB
#define LTR_Pin GPIO_PIN_9
#define LTR_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
