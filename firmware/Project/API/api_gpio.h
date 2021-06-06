#ifndef __API_GPIO_H_
#define __API_GPIO_H_

/* gpio definition */

#define LED1_ON()                HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)
#define LED1_OFF()               HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
#define LED1_TOGGLE()            HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)

#endif /* __API_GPIO_H_ */

