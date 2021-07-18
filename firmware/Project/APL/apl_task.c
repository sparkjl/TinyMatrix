#include "includes.h"

void Task_Handle(void)
{
  api_task_handle();
}

void Task_Start(void)
{
  /* add your task here */
  api_task_create(Task_SysdataHandle, 2000);
  api_task_create(Task_KeyScan, 30);
  api_task_create(Task_MatrixBlink, 1000);
  api_task_create(Task_MatrixShift, 160);
  api_task_create(Task_LED1, 1000);
  api_task_create(Task_MenuHandle, 100);
  api_task_create(Task_FontHandle, 10);
  //api_task_create(Task_UartTx, 50);
}

void Task_SysdataHandle(void)
{
  if(apl_sys_data_changed())
  {
    apl_sys_data_write();
  }
}

void Task_MatrixDisplay(void)
{
  if(tim2_is_up == 1)
  {
    api_tim_handle();
    tim2_is_up = 0;
  }
}

void Task_MatrixBlink(void)
{
  static uint8_t r = 255, g = 255, b = 255;

#if 1
  if(hub75_blink)
  {
    if(hub75_color++ == HUB75_Color_White)
      hub75_color = HUB75_Color_Black;
  }
#else
  bsp_hub75_write_panel(r,g,b,10,10);
  r -= 10;
  g -= 10;
  b -= 10;
#endif

}

void Task_MatrixShift(void)
{
#if 1
  apl_font_rolling( 0, sys_data.font_text[0], 16, &roll[0]);
  apl_font_rolling(16, sys_data.font_text[1], 16, &roll[1]);
  apl_font_rolling(32, sys_data.font_text[2], 16, &roll[2]);
  apl_font_rolling(48, sys_data.font_text[3], 16, &roll[3]);
#else
  apl_led_matrix_left_shift( 0, 16, 1);
  apl_led_matrix_left_shift(16, 16, 1);
  apl_led_matrix_left_shift(32, 16, 1);
  apl_led_matrix_left_shift(50, 16, 1);
#endif
}

void Task_MatrixTest(void)
{
  static char i = 0;

  if(i == 0)
  {
    HUB75_OE_L();
    HUB75_CLK_L();
    HUB75_LAT_L();
    HUB75_DR1_L();
    HUB75_DG1_L();
    HUB75_DB1_L();
    HUB75_DR2_L();
    HUB75_DG2_L();
    HUB75_DB2_L();
    HUB75_A_L();
    HUB75_B_L();
    HUB75_C_L();
    HUB75_D_L();
    HUB75_E_L();
  }
  else
  {
    HUB75_OE_H();
    HUB75_CLK_H();
    HUB75_LAT_H();
    HUB75_DR1_H();
    HUB75_DG1_H();
    HUB75_DB1_H();
    HUB75_DR2_H();
    HUB75_DG2_H();
    HUB75_DB2_H();
    HUB75_A_H();
    HUB75_B_H();
    HUB75_C_H();
    HUB75_D_H();
    HUB75_E_H();
  }

  if(++i == 2)
    i = 0;
}

void Task_LED1(void)
{
  LED1_TOGGLE();
}

void Task_KeyScan(void)
{
  bsp_key_scan();
}

void Task_MenuHandle(void)
{
  apl_menu_handle();
}

void Task_FontHandle(void)
{
  if(font_mode == 0)
  {
  }
  else if(font_mode == 1)
  {
//    if(font_size == 12)
//      apl_font_upgrade(0);
//    else if(font_size == 16)
//      apl_font_upgrade(1);
//    else if(font_size == 24)
//      apl_font_upgrade(2);
    apl_ulink_handle();
  }
  else if(font_mode == 2)
  {
  }
}

void Task_UartTx(void)
{
  //api_uart_tx_start(&uart1, "---* KUKO Labs *---\r\n", 22);
  if(uart1.rx_state != UART_OVER)
    return;
  
  api_uart_tx_start(&uart1, uart1.rx_buff, uart1.rx_count);
  api_uart_rx_start(&uart1);
}

