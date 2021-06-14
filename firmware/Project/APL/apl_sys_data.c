#include "includes.h"

System_DataTypeDef  sys_data, sys_data_pre;

void apl_sys_data_read(void)
{
  bsp_w25qx_read((uint8_t *)&sys_data, SYS_DATA_ADDR, sizeof(sys_data));

  if(sys_data.initial_code != 0xAB54EF96)
  {
    sys_data.initial_code = 0xAB54EF96;
    strcpy((char*)sys_data.product_SN, SYS_PRODUCT_SN);
    strcpy((char*)sys_data.firmware_SN, SYS_FIRMWARE_SN);
    sys_data.display_color = HUB75_Color_Pink;
    sys_data.display_mode = 1;
    sys_data.display_language = 1;
    sys_data.font_size = 16;

    strcpy((char*)sys_data.font_text[0], "1st line display text: ");
    strcpy((char*)sys_data.font_text[1], "2nd line display text: ");
    strcpy((char*)sys_data.font_text[2], "3rd line display text: ");
    strcpy((char*)sys_data.font_text[3], "4th line display text: ");
    strcpy((char*)sys_data.font_text[4], "5th line display text: ");
    strcpy((char*)sys_data.font_text[5], "6th line display text: ");

    bsp_w25qx_write_sector((uint8_t *)&sys_data, SYS_DATA_ADDR, sizeof(sys_data));
  }

  memcpy(&sys_data_pre, &sys_data, sizeof(sys_data));

  hub75_color = sys_data.display_color;
  if(hub75_color == HUB75_Color_Black)
    hub75_blink = 1;
  else
    hub75_blink = 0;
}

void apl_sys_data_write(void)
{
  bsp_w25qx_write_sector((uint8_t *)&sys_data, SYS_DATA_ADDR, sizeof(sys_data));

  memcpy(&sys_data_pre, &sys_data, sizeof(sys_data));
}

uint8_t apl_sys_data_changed(void)
{
  uint8_t reval = 0;

  if(memcmp(&sys_data, &sys_data_pre, sizeof(sys_data)) == 0)
    reval = 0;
  else
    reval = 1;

  return reval;
}

