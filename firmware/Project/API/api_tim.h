#ifndef __API_TIM_H_
#define __API_TIM_H_

extern TIM_HandleTypeDef htim2;
extern uint8_t tim2_is_up;

void api_tim_start(void);
void api_tim_stop(void);
void api_tim_handle(void);

#endif /* __API_TIM_H_ */

