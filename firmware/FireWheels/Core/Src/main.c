/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "nrf24l01p.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
    CONTROL_BLUETOOTH,
    CONTROL_NRF24L01
} ControlMode_t;

typedef struct {
    int8_t left_x;    // Bajt 1
    int8_t left_y;    // Bajt 2
    int8_t right_x;   // Bajt 3
    int8_t right_y;   // Bajt 4
    uint16_t buttons; // Bajty 5-6
} ControllerData;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BUZZ_GPIO_Port GPIOB
#define BUZZ_Pin GPIO_PIN_8
#define BTSTATE_GPIO_Port GPIOB
#define BTSTATE_Pin GPIO_PIN_5
#define M1IN1_GPIO_Port GPIOB
#define M1IN1_Pin GPIO_PIN_12
#define M1IN2_GPIO_Port GPIOA
#define M1IN2_Pin GPIO_PIN_4
#define M2IN2_GPIO_Port GPIOB
#define M2IN2_Pin GPIO_PIN_14
#define M3IN1_GPIO_Port GPIOA
#define M3IN1_Pin GPIO_PIN_10
#define M3IN2_GPIO_Port GPIOB
#define M3IN2_Pin GPIO_PIN_15
#define M4IN1_GPIO_Port GPIOA
#define M4IN1_Pin GPIO_PIN_11
#define M4IN2_GPIO_Port GPIOA
#define M4IN2_Pin GPIO_PIN_12
#define CNS_GPIO_Port GPIOB
#define CNS_Pin GPIO_PIN_1
#define IRQ_GPIO_Port GPIOB
#define IRQ_Pin GPIO_PIN_0
#define PS1TRIG_GPIO_Port GPIOB
#define PS1TRIG_Pin GPIO_PIN_11
#define LED_SIG_GPIO_Port GPIOC
#define LED_SIG_Pin GPIO_PIN_15
#define LED_BRAKE_GPIO_Port GPIOC
#define LED_BRAKE_Pin GPIO_PIN_14
#define LED_FRONT_GPIO_Port GPIOC
#define LED_FRONT_Pin GPIO_PIN_13
#define BTN_GPIO_Port GPIOA
#define BTN_Pin GPIO_PIN_0

#define USE_ULTRASONIC 0

#define NRF24L01P_SPI (&hspi1)
#define NRF24L01P_SPI_CS_PIN_PORT GPIOB
#define NRF24L01P_SPI_CS_PIN_NUMBER GPIO_PIN_1
#define NRF24L01P_IRQ_PIN_PORT GPIOB
#define NRF24L01P_IRQ_PIN_NUMBER GPIO_PIN_0
#define NRF24L01P_PAYLOAD_LENGTH 6

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
ControlMode_t currentMode = CONTROL_NRF24L01;
osMessageQueueId_t controlQueue;
uint8_t rx_byte;
uint8_t bt_rx_buffer[6];
uint8_t bt_rx_index = 0;
volatile uint32_t lastDataTime = 0; // Czas ostatniego odebranego pakietu
ControllerData controlData = {0}; // Globalna struktura przechowująca dane sterujące

#if USE_ULTRASONIC
volatile uint32_t echo_start, echo_end;
volatile uint8_t echo_flag = 0;
#endif

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
void driveMotor(GPIO_TypeDef* IN1_Port, uint16_t IN1_Pin, GPIO_TypeDef* IN2_Port, uint16_t IN2_Pin, TIM_HandleTypeDef* htim, uint32_t Channel, int speed_percent);
void SG90_SetAngle(uint8_t angle);
float Battery_GetVoltage(void);
void LED_Front(uint8_t on);
void LED_Brake(uint8_t on);
void LED_Signal(uint8_t on);
uint8_t Button_IsPressed(void);
void ControlTask(void *pvParameters);
void BatteryTask(void *pvParameters);
void ButtonTask(void *pvParameters);
void StatusTask(void *pvParameters);
#if USE_ULTRASONIC
void UltrasonicTask(void *pvParameters);
#endif
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim1;
extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
extern ADC_HandleTypeDef hadc1;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
#if USE_ULTRASONIC
  MX_TIM1_Init();
#endif
  nrf24l01p_rx_init(2402, 0);

  controlQueue = osMessageQueueNew(30, sizeof(ControllerData), NULL);
    const osThreadAttr_t controlTask_attr = {
        .name = "ControlTask",
        .priority = osPriorityHigh,
        .stack_size = 1024
    };
    osThreadNew(ControlTask, NULL, &controlTask_attr);
    osThreadNew(ButtonTask, NULL, NULL);
    osThreadNew(StatusTask, NULL, NULL);
    #if USE_ULTRASONIC
      osThreadNew(UltrasonicTask, NULL, NULL);
      HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
    #endif

    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);

    driveMotor(M1IN1_GPIO_Port, M1IN1_Pin, M1IN2_GPIO_Port, M1IN2_Pin, &htim2, TIM_CHANNEL_1, 0);
    driveMotor(M2IN1_GPIO_Port, M2IN1_Pin, M2IN2_GPIO_Port, M2IN2_Pin, &htim2, TIM_CHANNEL_2, 0);
    driveMotor(M3IN1_GPIO_Port, M3IN1_Pin, M3IN2_GPIO_Port, M3IN2_Pin, &htim2, TIM_CHANNEL_3, 0);
    driveMotor(M4IN1_GPIO_Port, M4IN1_Pin, M4IN2_GPIO_Port, M4IN2_Pin, &htim2, TIM_CHANNEL_4, 0);
    SG90_SetAngle(90);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* Call init function for freertos objects (in cmsis_os2.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void ControlTask(void *pvParameters) {
    ControllerData data;
    while (1) {
         //Sprawdź, czy minęło 100 ms od ostatniego pakietu
        if (HAL_GetTick() - lastDataTime > 100) {
            // Zeruj controlData i zatrzymaj silniki
            controlData.left_x = 0;
            controlData.left_y = 0;
            controlData.right_x = 0;
            controlData.right_y = 0;
            controlData.buttons = 0;
            SG90_SetAngle(90); // Ustaw serwo na pozycję neutralną
            driveMotor(M1IN1_GPIO_Port, M1IN1_Pin, M1IN2_GPIO_Port, M1IN2_Pin, &htim2, TIM_CHANNEL_1, 0);
            driveMotor(M2IN1_GPIO_Port, M2IN1_Pin, M2IN2_GPIO_Port, M2IN2_Pin, &htim2, TIM_CHANNEL_2, 0);
            driveMotor(M3IN1_GPIO_Port, M3IN1_Pin, M3IN2_GPIO_Port, M3IN2_Pin, &htim2, TIM_CHANNEL_3, 0);
            driveMotor(M4IN1_GPIO_Port, M4IN1_Pin, M4IN2_GPIO_Port, M4IN2_Pin, &htim2, TIM_CHANNEL_4, 0);
            LED_Brake(1); // Włącz światła stopu
            LED_Front(0); // Wyłącz światła przednie
            HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, GPIO_PIN_RESET); // Wyłącz buzzer
        }

        // Czekaj na nowy pakiet z kolejki
        if (osMessageQueueGet(controlQueue, &data, NULL, 0) == osOK) {
        	if(currentMode == CONTROL_NRF24L01){
        		controlData = data;
				lastDataTime = HAL_GetTick();

				// Sterowanie robotem
				int speed = controlData.left_y;
				int angle = (controlData.right_x + 100) * 180 / 200;

				SG90_SetAngle((uint8_t)angle);
				driveMotor(M1IN1_GPIO_Port, M1IN1_Pin, M1IN2_GPIO_Port, M1IN2_Pin, &htim2, TIM_CHANNEL_1, speed * -1);
				driveMotor(M2IN1_GPIO_Port, M2IN1_Pin, M2IN2_GPIO_Port, M2IN2_Pin, &htim2, TIM_CHANNEL_2, speed * -1);
				driveMotor(M3IN1_GPIO_Port, M3IN1_Pin, M3IN2_GPIO_Port, M3IN2_Pin, &htim2, TIM_CHANNEL_3, speed);
				driveMotor(M4IN1_GPIO_Port, M4IN1_Pin, M4IN2_GPIO_Port, M4IN2_Pin, &htim2, TIM_CHANNEL_4, speed);

				LED_Brake(speed <= 0 ? 1 : 0);
				LED_Front(controlData.buttons & 0x01 ? 1 : 0);
				HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, (controlData.buttons & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        	}
        	else{
        		controlData = data;
				lastDataTime = HAL_GetTick();

				// Sterowanie robotem
				int speed = controlData.left_x;
				int angle = (controlData.left_y + 100) * 180 / 200;

				SG90_SetAngle((uint8_t)angle);
				driveMotor(M1IN1_GPIO_Port, M1IN1_Pin, M1IN2_GPIO_Port, M1IN2_Pin, &htim2, TIM_CHANNEL_1, speed * -1);
				driveMotor(M2IN1_GPIO_Port, M2IN1_Pin, M2IN2_GPIO_Port, M2IN2_Pin, &htim2, TIM_CHANNEL_2, speed * -1);
				driveMotor(M3IN1_GPIO_Port, M3IN1_Pin, M3IN2_GPIO_Port, M3IN2_Pin, &htim2, TIM_CHANNEL_3, speed);
				driveMotor(M4IN1_GPIO_Port, M4IN1_Pin, M4IN2_GPIO_Port, M4IN2_Pin, &htim2, TIM_CHANNEL_4, speed);

				LED_Brake(speed <= 0 ? 1 : 0);
				LED_Front(controlData.buttons & 0x01 ? 1 : 0);
				HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, (controlData.buttons & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        	}


            // Aktualizuj controlData

        }

        osDelay(10); // Krótkie opóźnienie, aby nie obciążać procesora
    }
}

void sendCommand(const char* cmd)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);
}

void BatteryTask(void *pvParameters) {
    while (1) {
        float voltage = Battery_GetVoltage();
        if (voltage < 2.0f) {
            for (int i = 0; i < 3; i++) {
                HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, GPIO_PIN_SET);
                osDelay(100);
                HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, GPIO_PIN_RESET);
                osDelay(100);
            }
        }
        osDelay(5000);
    }
}

void ButtonTask(void *pvParameters) {
    while (1) {
        if (Button_IsPressed()) {
            osDelay(20);
            if (Button_IsPressed()) {
                if (currentMode == CONTROL_BLUETOOTH) {
                    currentMode = CONTROL_NRF24L01;
                    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
                    HAL_UART_AbortReceive_IT(&huart1);
                } else {
                    currentMode = CONTROL_BLUETOOTH;
                    HAL_NVIC_DisableIRQ(EXTI0_IRQn);
                    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
                }
                HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, GPIO_PIN_SET);
                osDelay(200);
                HAL_GPIO_WritePin(BUZZ_GPIO_Port, BUZZ_Pin, GPIO_PIN_RESET);
            }
        }
        osDelay(10);
    }
}

void StatusTask(void *pvParameters) {
    while (1) {
        if (currentMode == CONTROL_BLUETOOTH) {
            LED_Signal(1);
            osDelay(500);
            LED_Signal(0);
            osDelay(500);
        } else if (currentMode == CONTROL_NRF24L01) {
            LED_Signal(1);
            osDelay(1000);
        }
        osDelay(10);
    }
}

#if USE_ULTRASONIC
void UltrasonicTask(void *pvParameters) {
    while (1) {
        HAL_GPIO_WritePin(PS1TRIG_GPIO_Port, PS1TRIG_Pin, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin(PS1TRIG_GPIO_Port, PS1TRIG_Pin, GPIO_PIN_RESET);

        echo_flag = 0;
        while (!echo_flag) {
            osDelay(10);
        }

        uint32_t time_us = echo_end - echo_start;
        float distance = time_us / 58.0f;

        if (distance < 20.0f) {
            // Możesz dodać akcję, np. zatrzymanie pojazdu
        }

        osDelay(100);
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim1 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET) {
            echo_start = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
        } else {
            echo_end = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            echo_flag = 1;
        }
    }
}
#endif

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == IRQ_Pin && currentMode == CONTROL_NRF24L01) {
        ControllerData data;
        nrf24l01p_rx_receive((uint8_t*)&data);

        if (osMessageQueueGetSpace(controlQueue) == 0) {
            ControllerData dummy;
            osMessageQueueGet(controlQueue, &dummy, NULL, 0);
        }

        lastDataTime = HAL_GetTick();
        osMessageQueuePut(controlQueue, &data, 0, 0);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart == &huart1 && currentMode == CONTROL_BLUETOOTH) {
        bt_rx_buffer[bt_rx_index++] = rx_byte;
        if (bt_rx_index >= 6) {
            ControllerData data;
            memcpy(&data, bt_rx_buffer, 6);
            lastDataTime = HAL_GetTick();
            osMessageQueuePut(controlQueue, &data, 0, 0);
            bt_rx_index = 0;
        }
        if(HAL_UART_Receive_IT(&huart1, &rx_byte, 1) == HAL_OK){
        	LED_Front(1);
        }
        else{
        	LED_Brake(1);
        };
    }
}

void driveMotor(GPIO_TypeDef* IN1_Port, uint16_t IN1_Pin, GPIO_TypeDef* IN2_Port, uint16_t IN2_Pin, TIM_HandleTypeDef* htim, uint32_t Channel, int speed_percent) {
    if (speed_percent > 0) {
        HAL_GPIO_WritePin(IN1_Port, IN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(IN2_Port, IN2_Pin, GPIO_PIN_RESET);
    } else if (speed_percent < 0) {
        HAL_GPIO_WritePin(IN1_Port, IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IN2_Port, IN2_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(IN1_Port, IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IN2_Port, IN2_Pin, GPIO_PIN_RESET);
    }
    if (speed_percent > 100) {
        speed_percent = 100;
    }
    if (speed_percent < -100) {
        speed_percent = -100;
    }
    __HAL_TIM_SET_COMPARE(htim, Channel, abs(speed_percent));
}

void SG90_SetAngle(uint8_t angle) {
    uint32_t ccr_value = 500 + (angle * 2000 / 180);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, ccr_value);
}

float Battery_GetVoltage(void) {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 10);
    uint32_t raw = HAL_ADC_GetValue(&hadc1);
    return ((float)raw / 4095.0f) * 3.3f * 3;
}

void LED_Front(uint8_t on) {
    HAL_GPIO_WritePin(LED_FRONT_GPIO_Port, LED_FRONT_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void LED_Brake(uint8_t on) {
    HAL_GPIO_WritePin(LED_BRAKE_GPIO_Port, LED_BRAKE_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void LED_Signal(uint8_t on) {
    HAL_GPIO_WritePin(LED_SIG_GPIO_Port, LED_SIG_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

uint8_t Button_IsPressed(void) {
    return HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin) == GPIO_PIN_RESET;
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM3 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM3)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
