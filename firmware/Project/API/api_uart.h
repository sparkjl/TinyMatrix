#ifndef __API_UART_H_
#define __API_UART_H_


//#define RS485_EN_H                 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET)
//#define RS485_EN_L                 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET)

#define UART_RT_TIMEOUT            (uint16_t)(2u)          //set timeout: 2ms
#define UART_BUFF_LEN              (uint16_t)(512u)        //buffer length

/* uart handler definition */
typedef struct
{
  uint8_t       rx_state;
  uint8_t       rx_cache;
  uint8_t       rx_buff[UART_BUFF_LEN];
  uint16_t      rx_count;
  uint16_t      rx_tick;

  uint8_t       tx_state;
  uint8_t       tx_buff[UART_BUFF_LEN];
  uint16_t      tx_count;
  uint16_t      tx_tick;

} Uart_StructTypeDef;

/* uart state definition */
typedef enum
{
  UART_READY    = 00U,
  UART_BUSY     = 01U,
  UART_OVER     = 02U

} Uart_StateTypeDef;

extern Uart_StructTypeDef  uart1,  uart2,  uart3;
extern UART_HandleTypeDef huart1, huart2, huart3;

void api_uart_tick(void);
void api_uart_init(void);
void api_uart_rx_start(Uart_StructTypeDef *p_uart);
void api_uart_tx_start(Uart_StructTypeDef *p_uart, uint8_t *p_data, uint16_t size);
void api_uart_buff_fill(uint8_t *p_buff, uint16_t *p_count, uint8_t *p_data, uint16_t size);

#endif /* __API_UART_H_ */

