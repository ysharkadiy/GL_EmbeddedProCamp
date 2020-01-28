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
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t buffTx[256];
uint16_t len, i;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;

osThreadId_t defaultTaskHandle;
osThreadId_t myT2_GreenLedHandle;
osThreadId_t myT3_PushButtonHandle;
osThreadId_t myT4_OrangeLedHandle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
void StartDefaultTask(void *argument);
void StartT2_GreenLed(void *argument);
void StartT3_PushButton(void *argument);
void StartT4_OrangeLed(void *argument);

/* USER CODE BEGIN PFP */

/* To use the HOOK function macross configUSE_IDLE_HOOK need to be set '1' in FreeRTOSConfig.h file */
void vApplicationIdleHook( void );

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
vTraceEnable(TRC_START);
  /* USER CODE END 2 */

  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

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
  /* definition and creation of defaultTask */
  const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
  };
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* definition and creation of myT2_GreenLed */
  const osThreadAttr_t myT2_GreenLed_attributes = {
    .name = "myT2_GreenLed",
    .priority = (osPriority_t) osPriorityLow,
    .stack_size = 128
  };
  myT2_GreenLedHandle = osThreadNew(StartT2_GreenLed, NULL, &myT2_GreenLed_attributes);

  /* definition and creation of myT3_PushButton */
  const osThreadAttr_t myT3_PushButton_attributes = {
    .name = "myT3_PushButton",
    .priority = (osPriority_t) osPriorityLow,
    .stack_size = 128
  };
  myT3_PushButtonHandle = osThreadNew(StartT3_PushButton, NULL, &myT3_PushButton_attributes);

  /* definition and creation of myT4_OrangeLed */
  const osThreadAttr_t myT4_OrangeLed_attributes = {
    .name = "myT4_OrangeLed",
    .priority = (osPriority_t) osPriorityLow,
    .stack_size = 128
  };
  myT4_OrangeLedHandle = osThreadNew(StartT4_OrangeLed, NULL, &myT4_OrangeLed_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
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

/*----------------Idle Hook------------------------------------*/
/* Define the variable to be incremented by the hook function. */
unsigned long ulIdleCycleCount = 0UL;

/* Idle hook functions MUST be called vApplicationIdleHook (), not accept
  no parameters, and return void. */
void vApplicationIdleHook (void)
{
	/* This hook function does nothing but increment the counter. */
	ulIdleCycleCount ++;
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  for (i=0; i<256; i++) buffTx[i] = i;
  len = sizeof(buffTx);
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
  HAL_UART_Transmit_DMA(&huart1, buffTx, len);
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_StartT2_GreenLed */
/**
* @brief Function implementing the myT2_GreenLed thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartT2_GreenLed */
void StartT2_GreenLed(void *argument)
{
  /* USER CODE BEGIN StartT2_GreenLed */
  /* Infinite loop */
  for(;;)
  {
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
    //osDelay(1000);
	  
	  /* Delay for a period of time. This delay is created due to using the vTaskDelay () call, which puts the task in state
      Blocked until the expiration of the delay period. The delay period is indicated in 'ticks', 
	  but you can use the portTICK_RATE_MS constant to convert (more user-friendly) milliseconds in ticks.
      In my case, the period is 1000 milliseconds = 1s. */
	  vTaskDelay( 1000 / portTICK_RATE_MS );
  }
  /* USER CODE END StartT2_GreenLed */
}

/* USER CODE BEGIN Header_StartT3_PushButton */
/**
* @brief Function implementing the myT3_PushButton thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartT3_PushButton */
void StartT3_PushButton(void *argument)
{
  /* USER CODE BEGIN StartT3_PushButton */
	unsigned portBASE_TYPE uxPriority;
	uxPriority = uxTaskPriorityGet( NULL );
  /* Infinite loop */
  for(;;)
  {
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)!=GPIO_PIN_RESET)
	{
       /* definition and creation of myT4_OrangeLed */
		const osThreadAttr_t myT4_OrangeLed_attributes = {
		.name = "myT4_OrangeLed",
		.priority = (osPriority_t) osPriorityLow,
		.stack_size = 128
		};
		myT4_OrangeLedHandle = osThreadNew(StartT4_OrangeLed, NULL, &myT4_OrangeLed_attributes);
		
		/* Change Priority of myT4_OrangeLed task */
		vTaskPrioritySet( myT4_OrangeLedHandle, ( uxPriority + 1 ) );
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
	   //vTaskDelete(myT4_OrangeLedHandle);
	   //vTaskDelete(NULL);
	}
    //osDelay(100);
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
	vTaskDelay( 100 / portTICK_RATE_MS );
  }
  /* USER CODE END StartT3_PushButton */
}

/* USER CODE BEGIN Header_StartT4_OrangeLed */
/**
* @brief Function implementing the myT4_OrangeLed thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartT4_OrangeLed */
void StartT4_OrangeLed(void *argument)
{
  /* USER CODE BEGIN StartT4_OrangeLed */
  /* Infinite loop */
	//for(;;)
	//{
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
	vTaskDelete(NULL);
    //osDelay(500);
	//  vTaskDelay( 500 / portTICK_RATE_MS );
	//}
  /* USER CODE END StartT4_OrangeLed */
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
