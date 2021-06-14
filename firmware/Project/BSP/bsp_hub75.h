#ifndef __BSP_HUB75_H_
#define __BSP_HUB75_H_

/* hub75 interface definition */
#define HUB75_PANEL_WIDTH        (uint8_t)(64u)
#define HUB75_PANEL_HEIGHT       (uint8_t)(64u)

#define HUB75_OE_H()             HAL_GPIO_WritePin(HUB75_OE_GPIO_Port, HUB75_OE_Pin, GPIO_PIN_SET)
#define HUB75_OE_L()             HAL_GPIO_WritePin(HUB75_OE_GPIO_Port, HUB75_OE_Pin, GPIO_PIN_RESET)
#define HUB75_CLK_H()            HAL_GPIO_WritePin(HUB75_CLK_GPIO_Port, HUB75_CLK_Pin, GPIO_PIN_SET)
#define HUB75_CLK_L()            HAL_GPIO_WritePin(HUB75_CLK_GPIO_Port, HUB75_CLK_Pin, GPIO_PIN_RESET)
#define HUB75_LAT_H()            HAL_GPIO_WritePin(HUB75_LAT_GPIO_Port, HUB75_LAT_Pin, GPIO_PIN_SET)
#define HUB75_LAT_L()            HAL_GPIO_WritePin(HUB75_LAT_GPIO_Port, HUB75_LAT_Pin, GPIO_PIN_RESET)
#define HUB75_DR1_H()            HAL_GPIO_WritePin(HUB75_DR1_GPIO_Port, HUB75_DR1_Pin, GPIO_PIN_SET)
#define HUB75_DR1_L()            HAL_GPIO_WritePin(HUB75_DR1_GPIO_Port, HUB75_DR1_Pin, GPIO_PIN_RESET)
#define HUB75_DG1_H()            HAL_GPIO_WritePin(HUB75_DG1_GPIO_Port, HUB75_DG1_Pin, GPIO_PIN_SET)
#define HUB75_DG1_L()            HAL_GPIO_WritePin(HUB75_DG1_GPIO_Port, HUB75_DG1_Pin, GPIO_PIN_RESET)
#define HUB75_DB1_H()            HAL_GPIO_WritePin(HUB75_DB1_GPIO_Port, HUB75_DB1_Pin, GPIO_PIN_SET)
#define HUB75_DB1_L()            HAL_GPIO_WritePin(HUB75_DB1_GPIO_Port, HUB75_DB1_Pin, GPIO_PIN_RESET)
#define HUB75_DR2_H()            HAL_GPIO_WritePin(HUB75_DR2_GPIO_Port, HUB75_DR2_Pin, GPIO_PIN_SET)
#define HUB75_DR2_L()            HAL_GPIO_WritePin(HUB75_DR2_GPIO_Port, HUB75_DR2_Pin, GPIO_PIN_RESET)
#define HUB75_DG2_H()            HAL_GPIO_WritePin(HUB75_DG2_GPIO_Port, HUB75_DG2_Pin, GPIO_PIN_SET)
#define HUB75_DG2_L()            HAL_GPIO_WritePin(HUB75_DG2_GPIO_Port, HUB75_DG2_Pin, GPIO_PIN_RESET)
#define HUB75_DB2_H()            HAL_GPIO_WritePin(HUB75_DB2_GPIO_Port, HUB75_DB2_Pin, GPIO_PIN_SET)
#define HUB75_DB2_L()            HAL_GPIO_WritePin(HUB75_DB2_GPIO_Port, HUB75_DB2_Pin, GPIO_PIN_RESET)
#define HUB75_A_H()              HAL_GPIO_WritePin(HUB75_A_GPIO_Port, HUB75_A_Pin, GPIO_PIN_SET)
#define HUB75_A_L()              HAL_GPIO_WritePin(HUB75_A_GPIO_Port, HUB75_A_Pin, GPIO_PIN_RESET)
#define HUB75_B_H()              HAL_GPIO_WritePin(HUB75_B_GPIO_Port, HUB75_B_Pin, GPIO_PIN_SET)
#define HUB75_B_L()              HAL_GPIO_WritePin(HUB75_B_GPIO_Port, HUB75_B_Pin, GPIO_PIN_RESET)
#define HUB75_C_H()              HAL_GPIO_WritePin(HUB75_C_GPIO_Port, HUB75_C_Pin, GPIO_PIN_SET)
#define HUB75_C_L()              HAL_GPIO_WritePin(HUB75_C_GPIO_Port, HUB75_C_Pin, GPIO_PIN_RESET)
#define HUB75_D_H()              HAL_GPIO_WritePin(HUB75_D_GPIO_Port, HUB75_D_Pin, GPIO_PIN_SET)
#define HUB75_D_L()              HAL_GPIO_WritePin(HUB75_D_GPIO_Port, HUB75_D_Pin, GPIO_PIN_RESET)
#define HUB75_E_H()              HAL_GPIO_WritePin(HUB75_E_GPIO_Port, HUB75_E_Pin, GPIO_PIN_SET)
#define HUB75_E_L()              HAL_GPIO_WritePin(HUB75_E_GPIO_Port, HUB75_E_Pin, GPIO_PIN_RESET)

/* hub75 color definition */
typedef enum
{
  HUB75_Color_Black       = 00U,
  HUB75_Color_Red         = 01U,
  HUB75_Color_Green       = 02U,
  HUB75_Color_Yellow      = 03U,
  HUB75_Color_Blue        = 04U,
  HUB75_Color_Pink        = 05U,
  HUB75_Color_Cyan        = 06U,
  HUB75_Color_White       = 07U

} HUB75_ColorTypeDef;

extern uint8_t hub75_buff[HUB75_PANEL_WIDTH/8 * HUB75_PANEL_HEIGHT];
extern uint8_t hub75_color;
extern uint8_t hub75_blink;

extern uint8_t hub75_panel_buff[HUB75_PANEL_WIDTH * HUB75_PANEL_HEIGHT / 2 * 3];

void bsp_hub75_init(void);
void bsp_hub75_write_byte(uint8_t p_buff[], uint8_t color);
void bsp_hub75_write_pixel(uint8_t p_buff[]);
void bsp_hub75_write_panel(uint8_t R, uint8_t G, uint8_t B, uint16_t row, uint16_t column);


#endif /* __BSP_HUB75_H_ */

