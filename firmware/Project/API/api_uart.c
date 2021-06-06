#include "includes.h"

Uart_StructTypeDef  uart1,  uart2,  uart3;


void api_uart_tick(void)
{
  /* uart1 rx tick */
  if(uart1.rx_state == UART_BUSY)
  {
    uart1.rx_tick++;
    if(uart1.rx_tick > UART_RT_TIMEOUT)
    {
      uart1.rx_state = UART_OVER;
    }
  }

  /* uart1 tx tick */
  if(uart1.tx_state == UART_BUSY)
  {
    uart1.tx_tick++;
    if(uart1.tx_tick > UART_RT_TIMEOUT)
    {
      uart1.tx_state = UART_OVER;
    }
  }

  /* uart2 rx tick */
  if(uart2.rx_state == UART_BUSY)
  {
    uart2.rx_tick++;
    if(uart2.rx_tick > UART_RT_TIMEOUT)
    {
      uart2.rx_state = UART_OVER;
    }
  }

  /* uart2 tx tick */
  if(uart2.tx_state == UART_BUSY)
  {
    uart2.tx_tick++;
    if(uart2.tx_tick > UART_RT_TIMEOUT)
    {
      uart2.tx_state = UART_OVER;
    }
  }

  /* uart3 rx tick */
  if(uart3.rx_state == UART_BUSY)
  {
    uart3.rx_tick++;
    if(uart3.rx_tick > UART_RT_TIMEOUT)
    {
      uart3.rx_state = UART_OVER;
    }
  }

  /* uart3 tx tick */
  if(uart3.tx_state == UART_BUSY)
  {
    uart3.tx_tick++;
    if(uart3.tx_tick > UART_RT_TIMEOUT)
    {
      uart3.tx_state = UART_OVER;
    }
  }
}

void api_uart_init(void)
{
  HAL_UART_Receive_IT(&huart1, &uart1.rx_cache, 1);      //uart1 enable receive interrupt
  api_uart_rx_start(&uart1);                             //uart1 start to receive
  
}

/* non blocking mode uart receive */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART1)
  {
    if(uart1.rx_state != UART_OVER)
    {
      if(uart1.rx_count < UART_BUFF_LEN)
      {
        uart1.rx_buff[uart1.rx_count++] = uart1.rx_cache;
      }
      uart1.rx_state = UART_BUSY;
    }
    uart1.rx_tick = 0;
    HAL_UART_Receive_IT(&huart1, &uart1.rx_cache, 1);
  }

  if(huart->Instance == USART2)
  {
    if(uart2.rx_state != UART_OVER)
    {
      if(uart2.rx_count < UART_BUFF_LEN)
      {
        uart2.rx_buff[uart2.rx_count++] = uart2.rx_cache;
      }
      uart2.rx_state = UART_BUSY;
    }
    uart2.rx_tick = 0;
    HAL_UART_Receive_IT(&huart2, &uart2.rx_cache, 1);
  }

  if(huart->Instance == USART3)
  {
    if(uart3.rx_state != UART_OVER)
    {
      if(uart3.rx_count < UART_BUFF_LEN)
      {
        uart3.rx_buff[uart3.rx_count++] = uart3.rx_cache;
      }
      uart3.rx_state = UART_BUSY;
    }
    uart3.rx_tick = 0;
    HAL_UART_Receive_IT(&huart3, &uart3.rx_cache, 1);
  }

}

/* non blocking mode uart transfer */
/* Transfer Interrupt will run this func when transfer is over. */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART1)
  {
    if(uart1.tx_state != UART_OVER)
    {
      uart1.tx_state = UART_BUSY;
      uart1.tx_tick = 0;
    }
  }

  if(huart->Instance == USART2)
  {
    if(uart2.tx_state != UART_OVER)
    {
      uart2.tx_state = UART_BUSY;
      uart2.tx_tick = 0;
    }
  }

  if(huart->Instance == USART3)
  {
    if(uart3.tx_state != UART_OVER)
    {
      uart3.tx_state = UART_BUSY;
      uart3.tx_tick = 0;
    }
  }

}

void api_uart_rx_start(Uart_StructTypeDef *p_uart)
{
  p_uart->rx_state = UART_READY;
  p_uart->rx_count = 0;
  p_uart->rx_tick = 0;

}

void api_uart_tx_start(Uart_StructTypeDef *p_uart, uint8_t *p_data, uint16_t size)
{
  p_uart->tx_state = UART_READY;
  p_uart->tx_count = 0;
  p_uart->tx_tick = 0;

  if(p_uart == &uart1)
  {
    HAL_UART_Transmit_IT(&huart1, p_data, size);
  }
  else if(p_uart == &uart2)
  {
    HAL_UART_Transmit_IT(&huart2, p_data, size);
  }
  else if(p_uart == &uart3)
  {
    HAL_UART_Transmit_IT(&huart3, p_data, size);
  }
  while(p_uart->tx_state != UART_OVER);

}

void api_uart_buff_fill(uint8_t *p_buff, uint16_t *p_count, uint8_t *p_data, uint16_t size)
{
  for(uint16_t i=0; i<size; i++)
  {
    *(p_buff + (*p_count)++) = *(p_data++);
  }

}


