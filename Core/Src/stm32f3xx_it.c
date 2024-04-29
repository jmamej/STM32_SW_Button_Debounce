/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f3xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "gpio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define	NUM_OF_BUTTONS	4
#define MAX_STATE_THRESHOLD	10
#define MIN_STATE_THRESHOLD	-5
#define ACK_TIME	5
#define LONG_PRESS_TIME	500

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

int stop_tim_flag;
extern int button_flag[NUM_OF_BUTTONS];
int button_press_ack[NUM_OF_BUTTONS] = {0,0,0,0};
extern int button_press_counter[NUM_OF_BUTTONS];
extern int button_long_press_counter[NUM_OF_BUTTONS];
extern int button_press_state[NUM_OF_BUTTONS], button_press_timer[NUM_OF_BUTTONS];
GPIO_TypeDef* button_ports[NUM_OF_BUTTONS] = {BUTTON_A_GPIO_Port, BUTTON_B_GPIO_Port, BUTTON_C_GPIO_Port, BUTTON_D_GPIO_Port};
uint16_t button_pins[NUM_OF_BUTTONS] = {BUTTON_A_Pin, BUTTON_B_Pin, BUTTON_C_Pin, BUTTON_D_Pin};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(BUTTON_C_Pin);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(BUTTON_D_Pin);
  HAL_GPIO_EXTI_IRQHandler(BUTTON_A_Pin);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  for(int i = 0; i < NUM_OF_BUTTONS; i++)
  {
	  if(button_flag[i]){
		  HAL_GPIO_ReadPin(button_ports[i], button_pins[i]) ? button_press_state[i]-- : button_press_state[i]++;

		  button_press_timer[i]++;

		  if(button_press_state[i] >= ACK_TIME)	button_press_ack[i] = 1;

		  //if(button_press_ack[i])	button_press_timer[i]++;
		  if(button_press_state[i] > MAX_STATE_THRESHOLD)	button_press_state[i] = MAX_STATE_THRESHOLD;
		  else if(button_press_state[i] < MIN_STATE_THRESHOLD)
		  {
			  if(button_press_ack[i]){
				  button_press_timer[i] > LONG_PRESS_TIME ? button_long_press_counter[i]++ : button_press_counter[i]++;
				  button_press_ack[i] = 0;
			  }

			  button_flag[i] = 0;

			  stop_tim_flag = button_flag[0] + button_flag[1] + button_flag[2] + button_flag[3];
			  //printf("%d %d %d %d\n", button_flag[0], button_flag[1], button_flag[2], button_flag[3]);

			  if(!stop_tim_flag){
				  //printf("stop_tim_flag = 0\n");
				  HAL_TIM_Base_Stop_IT(&htim2);
				  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
			  }

			  switch(i)
			  {
				  case 0:
					  printf("Button A pressed for %d ms - short_counter: %d - long_counter: %d\n", button_press_timer[i], button_press_counter[i], button_long_press_counter[i]);
					  break;
				  case 1:
					  printf("Button B pressed for %d ms - short_counter: %d - long_counter: %d\n", button_press_timer[i], button_press_counter[i], button_long_press_counter[i]);
					  break;
				  case 2:
					  printf("Button C pressed for %d ms - short_counter: %d - long_counter: %d\n", button_press_timer[i], button_press_counter[i], button_long_press_counter[i]);
					  break;
				  case 3:
					  printf("Button D pressed for %d ms - short_counter: %d - long_counter: %d\n", button_press_timer[i], button_press_counter[i], button_long_press_counter[i]);
					  break;
			  }
		  }
	  }
  }






  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(BUTTON_B_Pin);
  HAL_GPIO_EXTI_IRQHandler(B1_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
