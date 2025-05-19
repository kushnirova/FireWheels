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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_FRONT_Pin GPIO_PIN_13
#define LED_FRONT_GPIO_Port GPIOC
#define LED_BRAKE_Pin GPIO_PIN_14
#define LED_BRAKE_GPIO_Port GPIOC
#define LED_SIG_Pin GPIO_PIN_15
#define LED_SIG_GPIO_Port GPIOC
#define BTN_Pin GPIO_PIN_0
#define BTN_GPIO_Port GPIOA
#define BATT_Pin GPIO_PIN_1
#define BATT_GPIO_Port GPIOA
#define M3PWM_Pin GPIO_PIN_2
#define M3PWM_GPIO_Port GPIOA
#define M4PWM_Pin GPIO_PIN_3
#define M4PWM_GPIO_Port GPIOA
#define M1IN2_Pin GPIO_PIN_4
#define M1IN2_GPIO_Port GPIOA
#define IRQ_Pin GPIO_PIN_0
#define IRQ_GPIO_Port GPIOB
#define CNS_Pin GPIO_PIN_1
#define CNS_GPIO_Port GPIOB
#define PS1TRIG_Pin GPIO_PIN_10
#define PS1TRIG_GPIO_Port GPIOB
#define PS2TRIG_Pin GPIO_PIN_11
#define PS2TRIG_GPIO_Port GPIOB
#define M1IN1_Pin GPIO_PIN_12
#define M1IN1_GPIO_Port GPIOB
#define M2IN1_Pin GPIO_PIN_13
#define M2IN1_GPIO_Port GPIOB
#define M2IN2_Pin GPIO_PIN_14
#define M2IN2_GPIO_Port GPIOB
#define M3IN2_Pin GPIO_PIN_15
#define M3IN2_GPIO_Port GPIOB
#define PS1ECHO_Pin GPIO_PIN_8
#define PS1ECHO_GPIO_Port GPIOA
#define PS2ECHO_Pin GPIO_PIN_9
#define PS2ECHO_GPIO_Port GPIOA
#define M3IN1_Pin GPIO_PIN_10
#define M3IN1_GPIO_Port GPIOA
#define M4IN1_Pin GPIO_PIN_11
#define M4IN1_GPIO_Port GPIOA
#define M4IN2_Pin GPIO_PIN_12
#define M4IN2_GPIO_Port GPIOA
#define M1PWM_Pin GPIO_PIN_15
#define M1PWM_GPIO_Port GPIOA
#define M2PWM_Pin GPIO_PIN_3
#define M2PWM_GPIO_Port GPIOB
#define BTEN_Pin GPIO_PIN_4
#define BTEN_GPIO_Port GPIOB
#define BTSTATE_Pin GPIO_PIN_5
#define BTSTATE_GPIO_Port GPIOB
#define S2PWM_Pin GPIO_PIN_8
#define S2PWM_GPIO_Port GPIOB
#define S1PWM_Pin GPIO_PIN_9
#define S1PWM_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
