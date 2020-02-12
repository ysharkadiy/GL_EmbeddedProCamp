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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define Blue_LED GPIO_PIN_8 	///< Queue isn't created. Memmory isn't llocated.
#define Red_LED GPIO_PIN_9 		///< Could not send data to the queue.
#define Orange_LED GPIO_PIN_10 	///< Queue is empty.
#define Green_LED GPIO_PIN_11 	///< Could not receive from the queue.
#define Red_LED2 GPIO_PIN_13 	///< Queue is full.

#define Green_LED2 GPIO_PIN_15 	///< Add data to queue every 0.1 sec

#define LED_GPIO_Port GPIOE
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;

osThreadId_t SenderHandle;
osThreadId_t ReceiverHandle;
osMessageQueueId_t myQueue01Handle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
void SenderTask(void *argument);
void ReceiverTask(void *argument);

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

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of myQueue01 */
  const osMessageQueueAttr_t myQueue01_attributes = {
    .name = "myQueue01"
  };
  myQueue01Handle = osMessageQueueNew (256, sizeof(uint8_t), &myQueue01_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  if (myQueue01Handle != NULL)
  {
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Sender */
  const osThreadAttr_t Sender_attributes = {
    .name = "Sender",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
  };
  SenderHandle = osThreadNew(SenderTask, NULL, &Sender_attributes);

  /* definition and creation of Receiver */
  const osThreadAttr_t Receiver_attributes = {
    .name = "Receiver",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
  };
  ReceiverHandle = osThreadNew(ReceiverTask, NULL, &Receiver_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  }
  else
  {
	uint8_t buffTx[] = "Queue isn't created!\n\r";
	HAL_GPIO_WritePin(LED_GPIO_Port, Blue_LED, GPIO_PIN_RESET);osDelay(1000);
	HAL_GPIO_WritePin(LED_GPIO_Port, Blue_LED, GPIO_PIN_SET);
	HAL_UART_Transmit_DMA(&huart1, buffTx, sizeof(buffTx));
  }
  
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

/* USER CODE BEGIN Header_SenderTask */
/**
  * @brief  Function implementing the Sender1 thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_SenderTask */
void SenderTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  portBASE_TYPE xStatus;
  uint8_t lValueToSend = 0;
  /* Infinite loop */
  for(;;)
  {
	if(osMessageQueueGetCount( myQueue01Handle ) < 25)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, Red_LED2, GPIO_PIN_RESET);
		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_SET) 
		{
			if(lValueToSend < 25) lValueToSend++;
			else lValueToSend = 0;

			xStatus = osMessageQueuePut( myQueue01Handle, &lValueToSend, NULL, 0);
			HAL_GPIO_TogglePin(LED_GPIO_Port, Green_LED2);

			if( xStatus != osOK)
			{
				uint8_t buffTx[] = "Could not send to the queue.\r\n";
				HAL_GPIO_WritePin(LED_GPIO_Port, Red_LED, GPIO_PIN_RESET);osDelay(1000);
				HAL_GPIO_WritePin(LED_GPIO_Port, Red_LED, GPIO_PIN_SET);
				HAL_UART_Transmit_DMA(&huart1, buffTx, sizeof(buffTx));
			}
		}	
	}
	else
	{
		uint8_t buffTx[] = "Queue is full!\r\n";
		HAL_GPIO_WritePin(LED_GPIO_Port, Red_LED2, GPIO_PIN_SET);
		HAL_UART_Transmit_DMA(&huart1, buffTx, sizeof(buffTx));
		osDelay(2*1000);//2sec
	}
	osDelay(100);
  }
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_ReceiverTask */
/**
* @brief Function implementing the Receiver thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ReceiverTask */
void ReceiverTask(void *argument)
{
  /* USER CODE BEGIN ReceiverTask */
  uint8_t lReceivedValue;
  portBASE_TYPE xStatus;
  /* Infinite loop */
  for(;;)
  {
	if( osMessageQueueGetCount( myQueue01Handle ) != 0 )
	{
		xStatus = osMessageQueueGet( myQueue01Handle, &lReceivedValue, NULL, 100);
		if( xStatus == osOK )
		{
			uint8_t buffTx[30] = "";
			sprintf(buffTx, "Received = %d!\r\n", lReceivedValue);
			HAL_UART_Transmit_DMA(&huart1, buffTx, sizeof(buffTx));
			osDelay(50);
		}
		else
		{
			uint8_t buffTx[] = "Could not receive from the queue.\r\n";
			HAL_GPIO_WritePin(LED_GPIO_Port, Green_LED, GPIO_PIN_RESET);osDelay(1000);
			HAL_GPIO_WritePin(LED_GPIO_Port, Green_LED, GPIO_PIN_SET);
			HAL_UART_Transmit_DMA(&huart1, buffTx, sizeof(buffTx));
			osDelay(50);
		}
	}
	else
	{
		uint8_t buffTx[] = "Queue is empty!\r\n";
		HAL_GPIO_WritePin(LED_GPIO_Port, Orange_LED, GPIO_PIN_RESET);osDelay(1000);
		HAL_GPIO_WritePin(LED_GPIO_Port, Orange_LED, GPIO_PIN_SET);
		HAL_UART_Transmit_DMA(&huart1, buffTx, sizeof(buffTx));
		osDelay(5*1000);//5sec
	}
	osDelay(1000);
  }
  /* USER CODE END ReceiverTask */
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
