#include "includes.h"

uint8_t tim2_is_up = 0;

void api_tim_start(void)
{
  HAL_TIM_Base_Start_IT(&htim2);
}

void api_tim_stop(void)
{
  HAL_TIM_Base_Stop_IT(&htim2);
}

void api_tim_handle(void)
{
  //static uint8_t tim_count = 15;

  /*
    HUB75_PANEL_HEIGHT = 64pix
    Freq(LED_Matrix)   = 60Hz
    Freq(TIM_Period)   = Freq(LED_Matrix) * HUB75_PANEL_HEIGHT / 2 * 15 = 60 * 64 / 2 * 15 = 28800Hz
    Period(LED_Matrix_PLANE_0) = TIM_Period * 8;
    Period(LED_Matrix_PLANE_1) = TIM_Period * 4;
    Period(LED_Matrix_PLANE_2) = TIM_Period * 2;
    Period(LED_Matrix_PLANE_3) = TIM_Period * 1;
  */

  //if( (tim_count == 15) || (tim_count == 7) || (tim_count == 3) || (tim_count == 1) )
  //{
    bsp_hub75_write_pixel(hub75_panel_buff);
  //}
  
  //if(tim_count > 1)
  //{
  //  tim_count--;
  //}
  //else
  //{
  //  tim_count = 15;
  //}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM2)
  {
    //api_tim_handle();
    tim2_is_up = 1;
  }

}


