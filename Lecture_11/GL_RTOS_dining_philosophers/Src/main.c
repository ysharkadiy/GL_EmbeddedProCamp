/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "semphr.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;

osThreadId_t myTask01Handle;
osThreadId_t myTask02Handle;
osThreadId_t myTask03Handle;
osThreadId_t myTask04Handle;
osThreadId_t myTask05Handle;
osSemaphoreId_t myBinarySem01Handle;
osSemaphoreId_t myBinarySem02Handle;
osSemaphoreId_t myBinarySem03Handle;
osSemaphoreId_t myBinarySem04Handle;
osSemaphoreId_t myBinarySem05Handle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
void StartTask01(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void StartTask04(void *argument);
void StartTask05(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySem01 */
  const osSemaphoreAttr_t myBinarySem01_attributes = {
    .name = "myBinarySem01"
  };
  myBinarySem01Handle = osSemaphoreNew(1, 1, &myBinarySem01_attributes);

  /* definition and creation of myBinarySem02 */
  const osSemaphoreAttr_t myBinarySem02_attributes = {
    .name = "myBinarySem02"
  };
  myBinarySem02Handle = osSemaphoreNew(1, 1, &myBinarySem02_attributes);

  /* definition and creation of myBinarySem03 */
  const osSemaphoreAttr_t myBinarySem03_attributes = {
    .name = "myBinarySem03"
  };
  myBinarySem03Handle = osSemaphoreNew(1, 1, &myBinarySem03_attributes);

  /* definition and creation of myBinarySem04 */
  const osSemaphoreAttr_t myBinarySem04_attributes = {
    .name = "myBinarySem04"
  };
  myBinarySem04Handle = osSemaphoreNew(1, 1, &myBinarySem04_attributes);

  /* definition and creation of myBinarySem05 */
  const osSemaphoreAttr_t myBinarySem05_attributes = {
    .name = "myBinarySem05"
  };
  myBinarySem05Handle = osSemaphoreNew(1, 1, &myBinarySem05_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of myTask01 */
  const osThreadAttr_t myTask01_attributes = {
    .name = "myTask01",
    .priority = (osPriority_t) osPriorityLow,
    .stack_size = 64
  };
  myTask01Handle = osThreadNew(StartTask01, NULL, &myTask01_attributes);

  /* definition and creation of myTask02 */
  const osThreadAttr_t myTask02_attributes = {
    .name = "myTask02",
    .priority = (osPriority_t) osPriorityLow,
    .stack_size = 64
  };
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* definition and creation of myTask03 */
  const osThreadAttr_t myTask03_attributes = {
    .name = "myTask03",
    .priority = (osPriority_t) osPriorityLow,
    .stack_size = 64
  };
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

  /* definition and creation of myTask04 */
  const osThreadAttr_t myTask04_attributes = {
    .name = "myTask04",
    .priority = (osPriority_t) osPriorityLow,
    .stack_size = 64
  };
  myTask04Handle = osThreadNew(StartTask04, NULL, &myTask04_attributes);

  /* definition and creation of myTask05 */
  const osThreadAttr_t myTask05_attributes = {
    .name = "myTask05",
    .priority = (osPriority_t) osPriorityLow,
    .stack_size = 64
  };
  myTask05Handle = osThreadNew(StartTask05, NULL, &myTask05_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	uint8_t buffTx[] = "Tasks were created!\r\n";
	HAL_UART_Transmit_DMA(&huart1, buffTx, sizeof(buffTx));
	osDelay(100);
  /* USER CODE END RTOS_THREADS */

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

  /** Initializes the CPU, AHB and APB busses clocks 
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
  /** Initializes the CPU, AHB and APB busses clocks 
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LD4_Pin|LD3_Pin|LD5_Pin|LD7_Pin 
                          |LD9_Pin|LD10_Pin|LD8_Pin|LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD7_Pin 
                           LD9_Pin LD10_Pin LD8_Pin LD6_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD7_Pin 
                          |LD9_Pin|LD10_Pin|LD8_Pin|LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartTask01 */
/**
  * @brief  Function implementing the myTask01 thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartTask01 */
void StartTask01(void *argument)
{
  /* USER CODE BEGIN 5 */
	
  /* Infinite loop */
  for(;;)
  {
	if( xSemaphoreTake( myBinarySem01Handle, 10 ) == pdTRUE)
	{
		if( xSemaphoreTake( myBinarySem02Handle, 10 ) == pdTRUE)
		{
			uint8_t buffTx[] = "Philosopher_1 is eating!\r\n";
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
			HAL_UART_Transmit_DMA(&huart1, buffTx, sizeof(buffTx));
			//HAL_UART_Transmit(&huart1, buffTx, sizeof(buffTx), 25);
			xSemaphoreGive( myBinarySem02Handle );
		}
		xSemaphoreGive( myBinarySem01Handle );
	}
	else
	{
		xSemaphoreGive( myBinarySem02Handle );
	}
    osDelay(1000);
  }
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
	if( xSemaphoreTake( myBinarySem02Handle, 10 ) == pdTRUE)
	{
		if( xSemaphoreTake( myBinarySem03Handle, 10 ) == pdTRUE)
		{
			uint8_t buffTx[] = "Philosopher_2 is eating!\r\n";
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
			HAL_UART_Transmit_DMA(&huart1, buffTx, sizeof(buffTx));
			//HAL_UART_Transmit(&huart1, buffTx, sizeof(buffTx), 25);
			xSemaphoreGive( myBinarySem03Handle );
		}
		xSemaphoreGive( myBinarySem02Handle );
	}
	else
	{
		xSemaphoreGive( myBinarySem03Handle );
	}
    osDelay(500);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
	if( xSemaphoreTake( myBinarySem03Handle, 10 ) == pdTRUE)
	{
		if( xSemaphoreTake( myBinarySem04Handle, 10 ) == pdTRUE)
		{
			uint8_t buffTx[] = "Philosopher_3 is eating!\r\n";
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
			HAL_UART_Transmit_DMA(&huart1, buffTx, sizeof(buffTx));
			//HAL_UART_Transmit(&huart1, buffTx, sizeof(buffTx), 25);
			xSemaphoreGive( myBinarySem04Handle );
		}
		xSemaphoreGive( myBinarySem03Handle );
	}
	else
	{
		xSemaphoreGive( myBinarySem04Handle );
	}
    osDelay(900);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void *argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
  for(;;)
  {
//	if( xSemaphoreTake( myBinarySem04Handle, 10 ) == pdTRUE)
//	{
//		if( xSemaphoreTake( myBinarySem05Handle, 10 ) == pdTRUE)
//		{
//			uint8_t buffTx[] = "Philosopher_4 is eating!\r\n";
//			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
//			HAL_UART_Transmit_DMA(&huart1, buffTx, sizeof(buffTx));
//			xSemaphoreGive( myBinarySem05Handle );
//		}
//		xSemaphoreGive( myBinarySem04Handle );
//	}
//	else
//	{
//		xSemaphoreGive( myBinarySem05Handle );
//	}
    osDelay(1000);
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
void StartTask05(void *argument)
{
  /* USER CODE BEGIN StartTask05 */
  /* Infinite loop */
  for(;;)
  {
//	if( xSemaphoreTake( myBinarySem05Handle, 10 ) == pdTRUE)
//	{
//		if( xSemaphoreTake( myBinarySem01Handle, 10 ) == pdTRUE)
//		{
//			uint8_t buffTx[] = "Philosopher_5 is eating!\r\n";
//			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
//			HAL_UART_Transmit_DMA(&huart1, buffTx, sizeof(buffTx));
//			xSemaphoreGive( myBinarySem01Handle );
//		}
//		xSemaphoreGive( myBinarySem05Handle );
//	}
//	else
//	{
//		xSemaphoreGive( myBinarySem01Handle );
//	}
    osDelay(100);
  }
  /* USER CODE END StartTask05 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
