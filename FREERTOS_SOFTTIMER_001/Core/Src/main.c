/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
// #include "cmsis_os.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
//osThreadId led1TaskHandle;
//osThreadId led2TaskHandle;
//osTimerId PTCallbackHandle;
//osTimerId OSTCallbackHandle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
//void StartLed1Task(void const * argument);
//void StartLed2Task02(void const * argument);
//void PTCallback01(void const * argument);
//void OSTCallback1(void const * argument);

void led1Task(void* argument);
void led2Task(void* argument);




/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void TimerCallback(xTimerHandle xTimer);
void someFunction();

xTimerHandle PTHandle;
xTimerHandle OTHandle;

xTaskHandle led1Handle;
xTaskHandle led2Handle;

/* definition and creation of OSTCallback */
// osTimerDef(OSTCallback, OSTCallback1);
// OSTCallbackHandle = osTimerCreate(osTimer(OSTCallback), osTimerOnce, NULL);
void someFunction() {
    // Create and assign the timers
    PTHandle = xTimerCreate("timer1", pdMS_TO_TICKS(1000), pdTRUE, (void *)1, TimerCallback);
    OTHandle = xTimerCreate("timer2", pdMS_TO_TICKS(4000), pdFALSE, (void *)2, TimerCallback);

    // Other code...
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of PTCallback */
  // osTimerDef(PTCallback, PTCallback01);
  // PTCallbackHandle = osTimerCreate(osTimer(PTCallback), osTimerPeriodic, NULL);





  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of led1Task */
  //osThreadDef(led1Task, StartLed1Task, osPriorityNormal, 0, 128);
  // led1TaskHandle = osThreadCreate(osThread(led1Task), NULL);

  xTaskCreate(led1Task, "led1", 128, NULL, 1, &led1Handle);
  xTaskCreate(led2Task, "led2", 128, NULL, 1, &led2Handle);


  someFunction();

  /* definition and creation of led2Task */
  // osThreadDef(led2Task, StartLed2Task02, osPriorityNormal, 0, 128);
  // led2TaskHandle = osThreadCreate(osThread(led2Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  // osKernelStart();
  vTaskStartScheduler();
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartLed1Task */
/**
  * @brief  Function implementing the led1Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartLed1Task */
//void StartLed1Task(void const * argument)
//{
//  /* USER CODE BEGIN 5 */
//	osTimerStart(PTCallbackHandle, 1000);
//
//  /* Infinite loop */
//  for(;;)
//  {
//	  HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
//	  osDelay(2000);
//  }
//  /* USER CODE END 5 */
//}

void led1Task(void* argument)
{
	xTimerStart(PTHandle,0);

	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
		vTaskDelay(2000);
	}


}

void led2Task(void* argument)
{


	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == 1)
		{
			while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0));
			xTimerStart(OTHandle,0);
		}
	}


}


/* USER CODE BEGIN Header_StartLed2Task02 */
/**
* @brief Function implementing the led2Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLed2Task02 */
//void StartLed2Task02(void const * argument)
//{
//  /* USER CODE BEGIN StartLed2Task02 */
//  /* Infinite loop */
//  for(;;)
//  {
//	  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == 1)
//	  {
//		  while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0));
//		  osTimerStart(OSTCallbackHandle, 4000);
//
//	  }
//
//    osDelay(20);
//  }
//  /* USER CODE END StartLed2Task02 */
//}

/* PTCallback01 function */
//void PTCallback01(void const * argument)
//{
//  /* USER CODE BEGIN PTCallback01 */
//
//	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_13);
//
//  /* USER CODE END PTCallback01 */
//}
//
///* OSTCallback1 function */
//void OSTCallback1(void const * argument)
//{
//  /* USER CODE BEGIN OSTCallback1 */
//
//	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_14);
//
//  /* USER CODE END OSTCallback1 */
//}

void TimerCallback(xTimerHandle xTimer)
{
	if(xTimer == PTHandle)
	{
		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_13);
	}
	else if(xTimer == OTHandle)
	{
		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_14);
	}


}






/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
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
