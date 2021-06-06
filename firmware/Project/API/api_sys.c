#include "includes.h"

#pragma optimize= none
void delay_us(uint32_t n_us)
{
  uint32_t n = (uint32_t)(CPU_F * (double)n_us / 1000000.0);
  
  while(n--)
  {
    __no_operation();
  }
}

void HAL_SYSTICK_Callback(void)
{
  api_task_tick();
  api_uart_tick();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* POWER_FAIL_5V_Pin */
  if(GPIO_Pin == GPIO_PIN_8)
  {

  }
}

