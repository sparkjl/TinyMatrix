#include "includes.h"

void bsp_key_scan(void)
{
  if(HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin) == GPIO_PIN_RESET)
    key.key1++;

  if(HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin) == GPIO_PIN_RESET)
    key.key2++;

  if(HAL_GPIO_ReadPin(KEY_3_GPIO_Port, KEY_3_Pin) == GPIO_PIN_RESET)
    key.key3++;

  if(HAL_GPIO_ReadPin(KEY_4_GPIO_Port, KEY_4_Pin) == GPIO_PIN_RESET)
    key.key4++;

}

uint8_t bsp_key_read(void)
{
  uint8_t  key_value = 0;
  uint8_t *p_key = NULL;

  if((HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin) == GPIO_PIN_SET) &&
     (HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin) == GPIO_PIN_SET) &&
     (HAL_GPIO_ReadPin(KEY_3_GPIO_Port, KEY_3_Pin) == GPIO_PIN_SET) &&
     (HAL_GPIO_ReadPin(KEY_4_GPIO_Port, KEY_4_Pin) == GPIO_PIN_SET))
  {
    p_key = &key.key1;
    for(uint8_t i=0; i<4; i++)
    {
      if(*p_key >= KEY_SHORT_COUNT)
      {
        key_value = i;
        key_value <<= 4;
        key_value |= 0x01;
        if(*p_key >= KEY_LONG_COUNT)
          key_value |= 0x02;
      }
      p_key++;
    }
    p_key = &key.key1;
    memset(p_key, 0, 4);
  }

  return key_value;
}

