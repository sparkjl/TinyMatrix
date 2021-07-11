#ifndef __APL_UART_LINK_H_
#define __APL_UART_LINK_H_

/* uart protocol data length */
#define UARTLINK_NUM                  (uint8_t)(255u)

/* uart protocol definition */
typedef struct
{
  uint8_t      addr;                    /* target address */
  uint8_t      func;                    /* function code */
  uint8_t      tick;                    /* increasing tick: 0-255 */

  uint8_t      length;                  /* data length */
  uint8_t      data[UARTLINK_NUM];      /* data field */

  uint8_t      crc16[2];                /* crc16 check */
} UartLink_HandleTypeDef;

extern UartLink_HandleTypeDef ulink;

extern uint8_t apl_ulink_handle(void);

#endif /* __APL_UART_LINK_H_ */

