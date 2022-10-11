/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define LED1_Pin GPIO_PIN_13
#define LED1_GPIO_Port GPIOC
#define HUB75_DR1_Pin GPIO_PIN_0
#define HUB75_DR1_GPIO_Port GPIOA
#define HUB75_DG1_Pin GPIO_PIN_1
#define HUB75_DG1_GPIO_Port GPIOA
#define HUB75_DB1_Pin GPIO_PIN_2
#define HUB75_DB1_GPIO_Port GPIOA
#define HUB75_DR2_Pin GPIO_PIN_3
#define HUB75_DR2_GPIO_Port GPIOA
#define HUB75_DG2_Pin GPIO_PIN_4
#define HUB75_DG2_GPIO_Port GPIOA
#define HUB75_DB2_Pin GPIO_PIN_5
#define HUB75_DB2_GPIO_Port GPIOA
#define HUB75_A_Pin GPIO_PIN_6
#define HUB75_A_GPIO_Port GPIOA
#define HUB75_B_Pin GPIO_PIN_7
#define HUB75_B_GPIO_Port GPIOA
#define HUB75_OE_Pin GPIO_PIN_0
#define HUB75_OE_GPIO_Port GPIOB
#define HUB75_CLK_Pin GPIO_PIN_1
#define HUB75_CLK_GPIO_Port GPIOB
#define HUB75_LAT_Pin GPIO_PIN_10
#define HUB75_LAT_GPIO_Port GPIOB
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define HUB75_C_Pin GPIO_PIN_8
#define HUB75_C_GPIO_Port GPIOA
#define HUB75_D_Pin GPIO_PIN_9
#define HUB75_D_GPIO_Port GPIOA
#define HUB75_E_Pin GPIO_PIN_10
#define HUB75_E_GPIO_Port GPIOA
#define KEY_4_Pin GPIO_PIN_15
#define KEY_4_GPIO_Port GPIOA
#define KEY_3_Pin GPIO_PIN_3
#define KEY_3_GPIO_Port GPIOB
#define KEY_2_Pin GPIO_PIN_4
#define KEY_2_GPIO_Port GPIOB
#define KEY_1_Pin GPIO_PIN_5
#define KEY_1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
