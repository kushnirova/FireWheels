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
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "nrf24l01p.h"
#include <stdlib.h>  // Dodano dla funkcji abs
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
GPIO_TypeDef* button_ports[] = {GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOB, GPIOB};
uint16_t button_pins[] = {GPIO_PIN_9, GPIO_PIN_8, GPIO_PIN_7, GPIO_PIN_6, GPIO_PIN_5, GPIO_PIN_4, GPIO_PIN_3, GPIO_PIN_15, GPIO_PIN_12, GPIO_PIN_11, GPIO_PIN_10, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11};

typedef struct {
    uint8_t state;    // 0 = niewciśnięty, 1 = wciśnięty
    uint8_t counter;  // Licznik dla debouncingu
} ButtonState;

typedef struct {
    int8_t left_x;    // Bajt 1
    int8_t left_y;    // Bajt 2
    int8_t right_x;   // Bajt 3
    int8_t right_y;   // Bajt 4
    uint16_t buttons; // Bajty 5-6 (14 bitów użytych)
} ControllerData;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DEBOUNCE_THRESHOLD 3  // 3 próbki przy 100 Hz = 30 ms debouncing
#define DEADZONE 10           // Domyślny deadzone w skali int8_t
#define LED_ON_DURATION 50    // 50 * 10 ms = 500 ms
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t adc_values[4];
ButtonState button_states[14];
ControllerData controller_data = {0};
uint8_t led_counter = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// Funkcja mapowania ADC na int8_t z deadzone
int8_t map_adc_to_int8(uint16_t adc, uint8_t deadzone) {
    int16_t temp = ((int32_t)adc - 2048) * 100 / 2048;  // Mapowanie 0-4095 na -100 do 100
    if (temp > 100) temp = 99;                         // Ograniczenie do 100
    if (temp < -100) temp = -99;                       // Ograniczenie do -100
    if (abs(temp) < deadzone) temp = 0;                 // Zastosowanie martwej strefy
    return (int8_t)temp;
}
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_values, 4);
  nrf24l01p_tx_init(2402, 0);
//  controller_data.left_x = 120;
//  controller_data.left_y = 120;
//  controller_data.right_x = 120;
//  controller_data.left_x = 120;
//  controller_data.buttons = 0xFFFF;
//  HAL_Delay(1000);
//  transmit_controller_data(&controller_data);
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
void transmit_controller_data(ControllerData* data) {
    // Cast the struct to a uint8_t* and pass it to the NRF24L01 transmit function
    nrf24l01p_tx_transmit((uint8_t*)data);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);  // Zapal diodę zawsze
    led_counter = LED_ON_DURATION;  // Świeć przez np. 500ms
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        // Odczyt i debouncing przycisków
        uint16_t new_buttons = 0;
        for (int i = 0; i < 14; i++) {
            uint8_t input = (HAL_GPIO_ReadPin(button_ports[i], button_pins[i]) == GPIO_PIN_RESET) ? 1 : 0;
            if (button_states[i].state == input) {
                button_states[i].counter = 0;
            } else {
                button_states[i].counter++;
                if (button_states[i].counter >= DEBOUNCE_THRESHOLD) {
                    button_states[i].state = input;
                    button_states[i].counter = 0;
                }
            }
            new_buttons |= (button_states[i].state << i);
        }

        // Odczyt i mapowanie wartości ADC
        int8_t new_left_x = map_adc_to_int8(adc_values[1], 0);
        int8_t new_left_y = map_adc_to_int8(adc_values[0], 0);
        int8_t new_right_y = map_adc_to_int8(adc_values[3], 0);
        int8_t new_right_x = map_adc_to_int8(adc_values[2], 0);

        // Wykrywanie zmian (triggery dla LED)
        bool trigger = false;
        if ((new_buttons & ~controller_data.buttons) != 0) trigger = true; // Wciśnięcie przycisku
        if (new_left_x != controller_data.left_x) trigger = true;
        if (new_left_y != controller_data.left_y) trigger = true;
        if (new_right_x != controller_data.right_x) trigger = true;
        if (new_right_y != controller_data.right_y) trigger = true;

        // Aktualizacja globalnej struktury
        controller_data.left_x = new_left_x;
        controller_data.left_y = new_left_y;
        controller_data.right_x = new_right_x;
        controller_data.right_y = new_right_y;
        controller_data.buttons = new_buttons;
        transmit_controller_data(&controller_data);
        // Sterowanie LED
        if (led_counter > 0) {
                    led_counter--;
                    if (led_counter == 0) {
                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);  // Wyłącz LED
                    }
                }

    }
}

/* USER CODE END 4 */

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
