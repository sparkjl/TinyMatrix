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

void apl_led_matrix_write_str(uint8_t *p_str, uint8_t row)
{
  uint32_t i = 0;
  uint8_t  j = 0, k = 0, n = 0;
  uint8_t *p = p_str;

#if 0
  uint8_t font_buff[32];
  uint32_t font_addr;
#endif

  if(row < (HUB75_PANEL_HEIGHT / 16))
    n = row * 16;
  else
    n = 0 * 16;

  while(*p != '\0')
  {
    /* Chinese font */
    if(*p > 0x80)
    {
#if 1
      for(i=0; i<(hzNum*2); i+=2)
      {
        if((*p == hzIndex[i])&&(*(p+1) == hzIndex[i+1]))
        {
          for(j=0; j<16; j++)
          {
            hub75_buff[(j+n)*(HUB75_PANEL_WIDTH/8)+k] = hzdot[i*16+j*2];
            if(k < (HUB75_PANEL_WIDTH/8))
            {
              hub75_buff[(j+n)*(HUB75_PANEL_WIDTH/8)+k+1] = hzdot[i*16+j*2+1];
            }  
          }
          break;
        }
      }
#else
      /* if GBKL<0x7F: Hp= ((GBKH-0x81)*190+GBKL-0x40)*(font_size*2) */
      if(*(p+1) < 0x7f)
      {
        font_addr = ((*p - 0x81) * 190 + *(p+1) - 0x40) * (16 * 2) + HZ_FONT_ADDR_0;
      }
      /* if GBKL>=0x80: Hp= ((GBKH-0x81)*190+GBKL-0x40)*(font_size*2) */
      else if(*(p+1) >= 0x80)
      {
        font_addr = ((*p - 0x81) * 190 + *(p+1) - 0x41) * (16 * 2) + HZ_FONT_ADDR_0;
      }
      bsp_w25qx_read(font_buff, font_addr, (16 * 2));
      for(j=0; j<16; j++)
      {
        hub75_buff[(j+n)*(HUB75_PANEL_WIDTH/8)+k] = font_buff[j*2];
        if(k < (HUB75_PANEL_WIDTH/8))
        {
          hub75_buff[(j+n)*(HUB75_PANEL_WIDTH/8)+k+1] = font_buff[j*2+1];
        }
      }
#endif
      k+=2;
      p+=2;
    }
    /* English font */
    else
    {
      for(i=0; i<charNum; i++)
      {
        if(*p == charIndex[i])
        {
          for(j=0; j<16; j++)
          {
            hub75_buff[(j+n)*(HUB75_PANEL_WIDTH/8)+k] = chardot[i*16+j];
          }
          break;
        }
      }
      k++;
      p++;
    }
    if(k >= (HUB75_PANEL_WIDTH/8))
      break;
  }

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

void apl_led_matrix_invert_row(uint8_t row)
{
  uint8_t  j = 0, k = 0, n = 0;
  uint8_t  buff_temp = 0;

  if(row < (HUB75_PANEL_HEIGHT / 16))
    n = row * 16;
  else
    n = 0 * 16;

  for(j=0; j<16; j++)
  {
    for(k=0; k<(HUB75_PANEL_WIDTH/8); k++)
    {
      buff_temp = ~hub75_buff[(j+n)*(HUB75_PANEL_WIDTH/8)+k];
      hub75_buff[(j+n)*(HUB75_PANEL_WIDTH/8)+k] = buff_temp;
    }
  }
  
}

