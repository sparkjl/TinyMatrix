#include "includes.h"

void apl_led_matrix_write_pixel(uint16_t x, uint16_t y, uint8_t color)
{
  uint32_t index = 0;
  uint8_t  mask = 0;
  
  if((x >= HUB75_PANEL_WIDTH) || (y >= HUB75_PANEL_HEIGHT))
    return;

  index = x / 8 + y * (HUB75_PANEL_WIDTH/8);
  mask  = 0x80 >> (x % 8);
  
  if(color)
    hub75_buff[index] |= mask;
  else
    hub75_buff[index] &= ~mask;

  return;
}

uint8_t apl_led_matrix_read_pixel(uint16_t x, uint16_t y)
{
  uint32_t index = 0;
  uint8_t  mask = 0;
  uint8_t  color = 0;

  if((x >= HUB75_PANEL_WIDTH) || (y >= HUB75_PANEL_HEIGHT))
    return 0;

  index = x / 8 + y * (HUB75_PANEL_WIDTH/8);
  mask  = 0x80 >> (x % 8);
  
  if(hub75_buff[index] & mask)
    color = 1;
  else
    color = 0;

  return color;
}

void apl_led_matrix_left_shift(uint16_t y, uint16_t height, uint16_t count)
{
  uint16_t y0 = y;
  uint16_t i  = 0;
  
  while(count--)
  {
    y = y0;
    while(y < (y0 + height))
    {
      for(i=0; i<HUB75_PANEL_WIDTH/8; i++)
      {
        if(i < HUB75_PANEL_WIDTH/8-1)
          hub75_buff[y*HUB75_PANEL_WIDTH/8+i] = (hub75_buff[y*HUB75_PANEL_WIDTH/8+i] << 1) | (hub75_buff[y*HUB75_PANEL_WIDTH/8+i+1] >> 7);
        else
          hub75_buff[y*HUB75_PANEL_WIDTH/8+i] = (hub75_buff[y*HUB75_PANEL_WIDTH/8+i] << 1);
      }

      y++;
      if(y >= HUB75_PANEL_HEIGHT)
        break;
    }
  }
}

