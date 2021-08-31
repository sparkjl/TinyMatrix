#include "includes.h"

uint8_t hub75_buff[HUB75_PANEL_WIDTH/8 * HUB75_PANEL_HEIGHT];
uint8_t hub75_color = HUB75_Color_Pink;
uint8_t hub75_blink = 0;

uint8_t hub75_panel_buff[HUB75_PANEL_WIDTH * HUB75_PANEL_HEIGHT / 2 * 3];

void send_clock(void)
{
  HUB75_CLK_H();
  HUB75_CLK_L();
}

void send_latch(unsigned char clock)
{
  HUB75_LAT_H();
  while(clock--)
  {
    send_clock();
  }
  HUB75_LAT_L();
}

void send_pwm_cycle(unsigned char cycle)
{
  while(cycle--)
  {
    HUB75_OE_H();
    HUB75_OE_L();
  }
}

void send_scan_line(unsigned char line)
{
  (line & 0x0001) ? HUB75_A_H() : HUB75_A_L();
  (line & 0x0002) ? HUB75_B_H() : HUB75_B_L();
  (line & 0x0004) ? HUB75_C_H() : HUB75_C_L();
  (line & 0x0008) ? HUB75_D_H() : HUB75_D_L();
  (line & 0x0010) ? HUB75_E_H() : HUB75_E_L();
}

void send_config(unsigned int data, unsigned char clock)
{
  unsigned char num = HUB75_PANEL_WIDTH/16;      // chip number
  unsigned int mask = 0x8000;

  clock = 16 - clock;

  while(num--)
  {
    for(unsigned char bit=0; bit<16; bit++)
    {
      mask = 0x8000 >> bit;

      if(data & mask)
      {
        HUB75_DR1_H();
        HUB75_DG1_H();
        HUB75_DB1_H();
        HUB75_DR2_H();
        HUB75_DG2_H();
        HUB75_DB2_H();
      }
      else
      {
        HUB75_DR1_L();
        HUB75_DG1_L();
        HUB75_DB1_L();
        HUB75_DR2_L();
        HUB75_DG2_L();
        HUB75_DB2_L();
      }

      if(num == 0 && bit == clock)
        HUB75_LAT_H();
      send_clock();
    }

    HUB75_LAT_L();
  }
}

void bsp_hub75_init(void)
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

#if HUB75_DRIVER_TYPE == 2
  /* Configure SRAM */
  send_latch(14);      // Pre-Active command
  send_latch(12);      // Enable all output channels
  send_latch(3);       // Vertical Sync
  send_latch(14);      // Pre-Active command
  send_config(0x1F70, 4);                  // Write config register 1 (4 latches)
  send_latch(14);      // Pre-Active command
  send_config(0xffff, 6);                  // Write config register 2 (6 latches)
  send_latch(14);      // Pre-Active command
  send_config(0x40F3, 8);                  // Write config register 3 (8 latches)
  send_latch(14);      // Pre-Active command
  send_config(0x0000, 10);                 // Write config register 4 (10 latches)
  send_latch(14);      // Pre-Active command
  send_config(0x0000, 2);                  // Write debug register (2 latches)
#endif

#if 1
  for(uint8_t i=0;i<32;i++)
  {
    for(uint8_t j=0;j<32;j++)
    {
      bsp_hub75_write_panel(255,153,0,i,j);
    }
    for(uint8_t k=32;k<64;k++)
    {
      bsp_hub75_write_panel(102,255,204,i,k);
    }
  }

  for(uint8_t i=32;i<64;i++)
  {
    for(uint8_t j=0;j<64;j++)
    {
      bsp_hub75_write_panel(255,0,255,i,j);
    }
  }
#endif
}

#if HUB75_DRIVER_TYPE == 0
void bsp_hub75_write_byte(uint8_t p_buff[], uint8_t color)
{
  static uint16_t row = 0;
  uint8_t data_r1, data_g1, data_b1, data_r2, data_g2, data_b2 = 0;

  /* write column data */
  for(uint16_t i=0; i<(HUB75_PANEL_WIDTH/8); i++)
  {
    data_r1 = data_g1 = data_b1 = 0;
    data_r2 = data_g2 = data_b2 = 0;

    /* color red */
    if(color & 0x01)
    {
      data_b1 = p_buff[row*(HUB75_PANEL_WIDTH/8)+i];
      data_b2 = p_buff[row*(HUB75_PANEL_WIDTH/8)+(HUB75_PANEL_WIDTH/8*HUB75_PANEL_HEIGHT/2)+i];
    }

    /* color green */
    if(color & 0x02)
    {
      data_r1 = p_buff[row*(HUB75_PANEL_WIDTH/8)+i];
      data_r2 = p_buff[row*(HUB75_PANEL_WIDTH/8)+(HUB75_PANEL_WIDTH/8*HUB75_PANEL_HEIGHT/2)+i];
    }

    /* color blue */
    if(color & 0x04)
    {
      data_g1 = p_buff[row*(HUB75_PANEL_WIDTH/8)+i];
      data_g2 = p_buff[row*(HUB75_PANEL_WIDTH/8)+(HUB75_PANEL_WIDTH/8*HUB75_PANEL_HEIGHT/2)+i];
    }

    /* horizontal 8 bits data */
    for(uint8_t k=0; k<8; k++)
    {
      ((data_r1>>(7-k)) & 0x01) ? HUB75_DR1_H() : HUB75_DR1_L();
      ((data_g1>>(7-k)) & 0x01) ? HUB75_DG1_H() : HUB75_DG1_L();
      ((data_b1>>(7-k)) & 0x01) ? HUB75_DB1_H() : HUB75_DB1_L();
      ((data_r2>>(7-k)) & 0x01) ? HUB75_DR2_H() : HUB75_DR2_L();
      ((data_g2>>(7-k)) & 0x01) ? HUB75_DG2_H() : HUB75_DG2_L();
      ((data_b2>>(7-k)) & 0x01) ? HUB75_DB2_H() : HUB75_DB2_L();

      HUB75_CLK_L();
      HUB75_CLK_H();
    }
  }

  HUB75_OE_H();
  HUB75_LAT_H();

  /* write row addr */
  (row & 0x0001) ? HUB75_A_H() : HUB75_A_L();
  (row & 0x0002) ? HUB75_B_H() : HUB75_B_L();
  (row & 0x0004) ? HUB75_C_H() : HUB75_C_L();
  (row & 0x0008) ? HUB75_D_H() : HUB75_D_L();
  (row & 0x0010) ? HUB75_E_H() : HUB75_E_L();
  HUB75_LAT_L();
  HUB75_OE_L();

  if(++row >= (HUB75_PANEL_HEIGHT/2))
    row = 0;

}
#endif

#if HUB75_DRIVER_TYPE == 2
void bsp_hub75_write_byte(uint8_t p_buff[], uint8_t color)
{
  static uint16_t row = 0;
  uint16_t data_sect1, data_sect2 = 0;
  uint16_t data_r1, data_g1, data_b1, data_r2, data_g2, data_b2 = 0;

  /* Vertical Sync */
  send_latch(3);

  for(uint16_t y=0; y<(HUB75_PANEL_HEIGHT/2); y++)      // (panel height/2) scan lines in 1 panel
  {
    for(uint16_t x=0; x<16; x++)      // 16 ouput channels in 1 chip
    {
      send_scan_line(y % 2 * (HUB75_PANEL_HEIGHT/4) + x);
      send_pwm_cycle(138);      // send 138 clock cycles for PWM generation inside the ICN2053 chips - this needs to be exactly 138 pulses

      /* write column data */
      for(uint16_t sect=0; sect<(HUB75_PANEL_WIDTH/16); sect++)
      {
        data_r1 = data_g1 = data_b1 = 0x0000;
        data_r2 = data_g2 = data_b2 = 0x0000;

        /* color red */
        if(color & 0x01)
        {
          data_g1 = 0xffff;
          data_g2 = 0xffff;
        }

        /* color green */
        if(color & 0x02)
        {
          data_b1 = 0xffff;
          data_b2 = 0xffff;
        }

        /* color blue */
        if(color & 0x04)
        {
          data_r1 = 0xffff;
          data_r2 = 0xffff;
        }

        /* get section data */
        data_sect1 = p_buff[y*(HUB75_PANEL_WIDTH/8)+sect*2];
        data_sect1 = (data_sect1 << 8) + p_buff[y*(HUB75_PANEL_WIDTH/8)+sect*2+1];
        data_sect2 = p_buff[y*(HUB75_PANEL_WIDTH/8)+(HUB75_PANEL_WIDTH/8*HUB75_PANEL_HEIGHT/2)+sect*2];
        data_sect2 = (data_sect2 << 8) + p_buff[y*(HUB75_PANEL_WIDTH/8)+(HUB75_PANEL_WIDTH/8*HUB75_PANEL_HEIGHT/2)+sect*2+1];

        if((data_sect1 << x) & 0x8000)
        {
          data_r1 = data_r1;
          data_g1 = data_g1;
          data_b1 = data_b1;
        }
        else
        {
          data_r1 = 0x0000;
          data_g1 = 0x0000;
          data_b1 = 0x0000;
        }

        if((data_sect2 << x) & 0x8000)
        {
          data_r2 = data_r2;
          data_g2 = data_g2;
          data_b2 = data_b2;
        }
        else
        {
          data_r2 = 0x0000;
          data_g2 = 0x0000;
          data_b2 = 0x0000;
        }

        /* horizontal 16 bits data */
        for(uint8_t bit=0; bit<16; bit++)
        {
          ((data_r1 << bit) & 0x8000) ? HUB75_DR1_H() : HUB75_DR1_L();
          ((data_g1 << bit) & 0x8000) ? HUB75_DG1_H() : HUB75_DG1_L();
          ((data_b1 << bit) & 0x8000) ? HUB75_DB1_H() : HUB75_DB1_L();
          ((data_r2 << bit) & 0x8000) ? HUB75_DR2_H() : HUB75_DR2_L();
          ((data_g2 << bit) & 0x8000) ? HUB75_DG2_H() : HUB75_DG2_L();
          ((data_b2 << bit) & 0x8000) ? HUB75_DB2_H() : HUB75_DB2_L();

          if(sect == (HUB75_PANEL_WIDTH/16-1) && bit == 15)
            HUB75_LAT_H();
          send_clock();
        }
        HUB75_LAT_L();
      }
    }
  }
}
#endif

void bsp_hub75_write_pixel(uint8_t p_buff[])
{
  static uint16_t plane = 0;
  static uint16_t row = 0;
  uint8_t data_r1, data_g1, data_b1, data_r2, data_g2, data_b2 = 0;

  static uint16_t bcm_cnt = 15;

  for(uint16_t i=0; i<HUB75_PANEL_WIDTH; i++)
  {
    if(plane == 0)
    {
      data_r1 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*2+i] >> 1 & 0x01; //plane3 bit1
      data_r2 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*2+i] >> 0 & 0x01; //plane3 bit0
      data_g1 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*1+i] >> 1 & 0x01; //plane2 bit1
      data_g2 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*1+i] >> 0 & 0x01; //plane2 bit0
      data_b1 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*0+i] >> 1 & 0x01; //plane1 bit1
      data_b2 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*0+i] >> 0 & 0x01; //plane1 bit0
    }
    else if(plane == 1)
    {
      data_r1 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*0+i] >> 5 & 0x01; //plane1 bit5
      data_r2 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*0+i] >> 2 & 0x01; //plane1 bit2
      data_g1 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*0+i] >> 6 & 0x01; //plane1 bit6
      data_g2 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*0+i] >> 3 & 0x01; //plane1 bit3
      data_b1 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*0+i] >> 7 & 0x01; //plane1 bit7
      data_b2 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*0+i] >> 4 & 0x01; //plane1 bit4
    }
    else if(plane == 2)
    {
      data_r1 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*1+i] >> 5 & 0x01; //plane2 bit5
      data_r2 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*1+i] >> 2 & 0x01; //plane2 bit2
      data_g1 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*1+i] >> 6 & 0x01; //plane2 bit6
      data_g2 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*1+i] >> 3 & 0x01; //plane2 bit3
      data_b1 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*1+i] >> 7 & 0x01; //plane2 bit7
      data_b2 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*1+i] >> 4 & 0x01; //plane2 bit4
    }
    else if(plane == 3)
    {
      data_r1 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*2+i] >> 5 & 0x01; //plane3 bit5
      data_r2 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*2+i] >> 2 & 0x01; //plane3 bit2
      data_g1 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*2+i] >> 6 & 0x01; //plane3 bit6
      data_g2 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*2+i] >> 3 & 0x01; //plane3 bit3
      data_b1 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*2+i] >> 7 & 0x01; //plane3 bit7
      data_b2 = p_buff[row*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*2+i] >> 4 & 0x01; //plane3 bit4
    }

#if 0
    (data_g1) ? HUB75_DR1_H() : HUB75_DR1_L();
    (data_b1) ? HUB75_DG1_H() : HUB75_DG1_L();
    (data_r1) ? HUB75_DB1_H() : HUB75_DB1_L();
    (data_g2) ? HUB75_DR2_H() : HUB75_DR2_L();
    (data_b2) ? HUB75_DG2_H() : HUB75_DG2_L();
    (data_r2) ? HUB75_DB2_H() : HUB75_DB2_L();
#else
    (data_g1) ? (GPIOA->BSRR = 0x00000001) : (GPIOA->BSRR = 0x00010000);
    (data_b1) ? (GPIOA->BSRR = 0x00000002) : (GPIOA->BSRR = 0x00020000);
    (data_r1) ? (GPIOA->BSRR = 0x00000004) : (GPIOA->BSRR = 0x00040000);
    (data_g2) ? (GPIOA->BSRR = 0x00000008) : (GPIOA->BSRR = 0x00080000);
    (data_b2) ? (GPIOA->BSRR = 0x00000010) : (GPIOA->BSRR = 0x00100000);
    (data_r2) ? (GPIOA->BSRR = 0x00000020) : (GPIOA->BSRR = 0x00200000);
#endif

#if 0
    HUB75_CLK_L();
    HUB75_CLK_H();
#else
    GPIOB->BSRR = 0x00020000;
    GPIOB->BSRR = 0X00000002;
#endif
  }

#if 0
  HUB75_OE_H();
  HUB75_LAT_H();
#else
  GPIOB->BSRR = 0X00000001;
  GPIOB->BSRR = 0X00000400;
#endif

  /* write row addr */
#if 0
  (row & 0x0001) ? HUB75_A_H() : HUB75_A_L();
  (row & 0x0002) ? HUB75_B_H() : HUB75_B_L();
  (row & 0x0004) ? HUB75_C_H() : HUB75_C_L();
  (row & 0x0008) ? HUB75_D_H() : HUB75_D_L();
  (row & 0x0010) ? HUB75_E_H() : HUB75_E_L();
  HUB75_LAT_L();
  HUB75_OE_L();
#else
  (row & 0x0001) ? (GPIOA->BSRR = 0x00000040) : (GPIOA->BSRR = 0x00400000);
  (row & 0x0002) ? (GPIOA->BSRR = 0x00000080) : (GPIOA->BSRR = 0x00800000);
  (row & 0x0004) ? (GPIOA->BSRR = 0x00000100) : (GPIOA->BSRR = 0x01000000);
  (row & 0x0008) ? (GPIOA->BSRR = 0x00000200) : (GPIOA->BSRR = 0x02000000);
  (row & 0x0010) ? (GPIOA->BSRR = 0x00000400) : (GPIOA->BSRR = 0x04000000);
  GPIOB->BSRR = 0X04000000;
  GPIOB->BSRR = 0X00010000;
#endif

#if 0
  if(bcm_cnt > 1)
  {
    bcm_cnt--;
    if(bcm_cnt == ((8>>plane)-1))
    {
      plane++;
    }
  }
  else
  {
    bcm_cnt = 15;
    plane = 0;
    if(++row == (HUB75_PANEL_HEIGHT/2))
    {
      row = 0;
    }
  }
#else
  /* BCM 8-4-2-1 */
  if(++row == (HUB75_PANEL_HEIGHT/4))
  {
    row = 0;
    if(bcm_cnt > 1)
    {
      bcm_cnt--;
      if(bcm_cnt == ((8>>plane)-1))
      {
        plane++;
      }
    }
    else
    {
      bcm_cnt = 15;
      plane = 0;
    }
  }
#endif

}

void bsp_hub75_write_panel(uint8_t R, uint8_t G, uint8_t B, uint16_t row, uint16_t column)
{
  uint8_t *p_plane1 = NULL, *p_plane2 = NULL, *p_plane3 = NULL;

  if((row >= HUB75_PANEL_HEIGHT) || (column >= HUB75_PANEL_WIDTH))
    return;

  p_plane1 = &hub75_panel_buff[row%(HUB75_PANEL_HEIGHT/2)*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*0+column];
  p_plane2 = &hub75_panel_buff[row%(HUB75_PANEL_HEIGHT/2)*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*1+column];
  p_plane3 = &hub75_panel_buff[row%(HUB75_PANEL_HEIGHT/2)*HUB75_PANEL_WIDTH+HUB75_PANEL_WIDTH*HUB75_PANEL_HEIGHT/2*2+column];

  if(row < (HUB75_PANEL_HEIGHT/2))      //Top
  {
    if((R >> 7) & 0x01) *p_plane3 |= (1 << 1);
    else                *p_plane3 &= ~(1 << 1);

    if((R >> 6) & 0x01) *p_plane1 |= (1 << 5);
    else                *p_plane1 &= ~(1 << 5);

    if((R >> 5) & 0x01) *p_plane2 |= (1 << 5);
    else                *p_plane2 &= ~(1 << 5);

    if((R >> 4) & 0x01) *p_plane3 |= (1 << 5);
    else                *p_plane3 &= ~(1 << 5);

    if((G >> 7) & 0x01) *p_plane2 |= (1 << 1);
    else                *p_plane2 &= ~(1 << 1);

    if((G >> 6) & 0x01) *p_plane1 |= (1 << 6);
    else                *p_plane1 &= ~(1 << 6);

    if((G >> 5) & 0x01) *p_plane2 |= (1 << 6);
    else                *p_plane2 &= ~(1 << 6);

    if((G >> 4) & 0x01) *p_plane3 |= (1 << 6);
    else                *p_plane3 &= ~(1 << 6);

    if((B >> 7) & 0x01) *p_plane1 |= (1 << 1);
    else                *p_plane1 &= ~(1 << 1);

    if((B >> 6) & 0x01) *p_plane1 |= (1 << 7);
    else                *p_plane1 &= ~(1 << 7);

    if((B >> 5) & 0x01) *p_plane2 |= (1 << 7);
    else                *p_plane2 &= ~(1 << 7);

    if((B >> 4) & 0x01) *p_plane3 |= (1 << 7);
    else                *p_plane3 &= ~(1 << 7);
  }
  else                                  //Bottom
  {
    if((R >> 7) & 0x01) *p_plane3 |= (1 << 0);
    else                *p_plane3 &= ~(1 << 0);

    if((R >> 6) & 0x01) *p_plane1 |= (1 << 2);
    else                *p_plane1 &= ~(1 << 2);

    if((R >> 5) & 0x01) *p_plane2 |= (1 << 2);
    else                *p_plane2 &= ~(1 << 2);

    if((R >> 4) & 0x01) *p_plane3 |= (1 << 2);
    else                *p_plane3 &= ~(1 << 2);

    if((G >> 7) & 0x01) *p_plane2 |= (1 << 0);
    else                *p_plane2 &= ~(1 << 0);

    if((G >> 6) & 0x01) *p_plane1 |= (1 << 3);
    else                *p_plane1 &= ~(1 << 3);

    if((G >> 5) & 0x01) *p_plane2 |= (1 << 3);
    else                *p_plane2 &= ~(1 << 3);

    if((G >> 4) & 0x01) *p_plane3 |= (1 << 3);
    else                *p_plane3 &= ~(1 << 3);

    if((B >> 7) & 0x01) *p_plane1 |= (1 << 0);
    else                *p_plane1 &= ~(1 << 0);

    if((B >> 6) & 0x01) *p_plane1 |= (1 << 4);
    else                *p_plane1 &= ~(1 << 4);

    if((B >> 5) & 0x01) *p_plane2 |= (1 << 4);
    else                *p_plane2 &= ~(1 << 4);

    if((B >> 4) & 0x01) *p_plane3 |= (1 << 4);
    else                *p_plane3 &= ~(1 << 4);
  }

}

