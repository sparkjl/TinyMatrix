#include "includes.h"

Menu_StateTypeDef menu_state = Menu_M;
uint8_t key_value = 0;
uint8_t set_item = 1;

void apl_menu_init(void)
{
  apl_menu_m_display((set_item-1)/3);
}

void apl_menu_handle(void)
{
  key_value = bsp_key_read();

  if(key_value)
  {
    switch(menu_state)
    {
      case Menu_M:
        apl_menu_m_callback();
        break;

      case Menu_1:
        apl_menu_1_callback();
        break;

      case Menu_2:
        apl_menu_2_callback();
        break;

      case Menu_3:
        break;

      default:
        break;
    }
  }
}

void apl_menu_m_callback(void)
{

  switch(key_value)
  {
    case KEY1_SHORT:
      if(set_item-- == 1)
        set_item = 3;
      apl_menu_m_display((set_item-1)/3);
      break;

    case KEY1_LONG:
      break;

    case KEY2_SHORT:
      if(set_item++ == 3)
        set_item = 1;
      apl_menu_m_display((set_item-1)/3);
      break;

    case KEY2_LONG:
      break;

    case KEY3_SHORT:
      if(set_item == 1)
      {
        menu_state = Menu_1;
        set_item = 1;
        apl_menu_1_display((set_item-1)/3);
      }
      else if(set_item == 2)
      {
        menu_state = Menu_2;
        set_item = 1;
        apl_menu_2_display((set_item-1)/3);
      }
      else if(set_item == 3)
      {
      }
      break;

    case KEY3_LONG:
      break;

    case KEY4_SHORT:
      break;

    case KEY4_LONG:
      break;

    default:
      break;
  }
}

void apl_menu_m_display(uint8_t page)
{
  apl_font_display(0, 0, HUB75_PANEL_WIDTH, 16, " SET UP ", 16, 0);
  //apl_led_matrix_write_str(" SET UP ", 0);
  if(page == 0)
  {
    apl_font_display(0, 16, HUB75_PANEL_WIDTH, 16, "1.Mode  ", 16, 0);
    apl_font_display(0, 32, HUB75_PANEL_WIDTH, 16, "2.Color ", 16, 0);
    apl_font_display(0, 48, HUB75_PANEL_WIDTH, 16, "3.Langua", 16, 0);
    apl_font_reverse(0, set_item*16, HUB75_PANEL_WIDTH, 16);
    //apl_led_matrix_write_str("1.Mode  ", 1);
    //apl_led_matrix_write_str("2.Color ", 2);
    //apl_led_matrix_write_str("3.Langua", 3);
    //apl_led_matrix_invert_row(set_item);
  }
}

void apl_menu_1_callback(void)
{

  switch(key_value)
  {
    case KEY1_SHORT:
      if(set_item-- == 1)
        set_item = 3;
      apl_menu_1_display((set_item-1)/3);
      break;

    case KEY1_LONG:
      break;

    case KEY2_SHORT:
      if(set_item++ == 3)
        set_item = 1;
      apl_menu_1_display((set_item-1)/3);
      break;

    case KEY2_LONG:
      break;

    case KEY3_SHORT:
      if(set_item == 1)
      {
        //memset(font_buff, 0, sizeof(font_buff));
        //bsp_w25qx_read(font_buff, HZ_FONT_ADDR_0, 256);
        font_mode = 0;
      }
      else if(set_item == 2)
      {
        //font_buff[0] = 0xad;
        //font_buff[1] = 0x34;
        //font_buff[2] = 0x56;
        //font_buff[3] = 0x6a;
        //font_buff[4] = 0xec;
        //font_buff[5] = 0x96;
        //font_buff[6] = 0x69;
        //font_buff[7] = 0x00;
        //bsp_w25qx_write(font_buff, HZ_FONT_ADDR_0, 256);
        font_mode = 1;
      }
      else if(set_item == 3)
      {
        apl_font_erase(0);
        font_mode = 2;
      }
      break;

    case KEY3_LONG:
      break;

    case KEY4_SHORT:
        menu_state = Menu_M;
        set_item = 1;
        apl_menu_m_display((set_item-1)/3);
        font_mode = 0;
      break;

    case KEY4_LONG:
      break;

    default:
      break;
  }
}

void apl_menu_1_display(uint8_t page)
{
  apl_font_display(0, 0, HUB75_PANEL_WIDTH, 16, "  MODE  ", 16, 0);
  //apl_led_matrix_write_str("  MODE  ", 0);
  if(page == 0)
  {
    apl_font_display(0, 16, HUB75_PANEL_WIDTH, 16, "1.Static", 16, 0);
    apl_font_display(0, 32, HUB75_PANEL_WIDTH, 16, "2.Dynami", 16, 0);
    apl_font_display(0, 48, HUB75_PANEL_WIDTH, 16, "3.Upgrad", 16, 0);
    apl_font_reverse(0, set_item*16, HUB75_PANEL_WIDTH, 16);
    //apl_led_matrix_write_str("1.Static", 1);
    //apl_led_matrix_write_str("2.Dynami", 2);
    //apl_led_matrix_write_str("3.Upgrad", 3);
    //apl_led_matrix_invert_row(set_item);
  }
}

void apl_menu_2_callback(void)
{

  switch(key_value)
  {
    case KEY1_SHORT:
      if(set_item-- == 1)
        set_item = 9;
      apl_menu_2_display((set_item-1)/3);
      break;

    case KEY1_LONG:
      break;

    case KEY2_SHORT:
      if(set_item++ == 9)
        set_item = 1;
      apl_menu_2_display((set_item-1)/3);
      break;

    case KEY2_LONG:
      break;

    case KEY3_SHORT:
      if(set_item == 1)
      {
        hub75_color = HUB75_Color_Red;
        hub75_blink = 0;
      }
      else if(set_item == 2)
      {
        hub75_color = HUB75_Color_Green;
        hub75_blink = 0;
      }
      else if(set_item == 3)
      {
        hub75_color = HUB75_Color_Yellow;
        hub75_blink = 0;
      }
      else if(set_item == 4)
      {
        hub75_color = HUB75_Color_Blue;
        hub75_blink = 0;
      }
      else if(set_item == 5)
      {
        hub75_color = HUB75_Color_Pink;
        hub75_blink = 0;
      }
      else if(set_item == 6)
      {
        hub75_color = HUB75_Color_Cyan;
        hub75_blink = 0;
      }
      else if(set_item == 7)
      {
        hub75_color = HUB75_Color_White;
        hub75_blink = 0;
      }
      else if(set_item == 8)
      {
        hub75_color = HUB75_Color_Black;
        hub75_blink = 1;
      }
      else if(set_item == 9)
      {
        apl_font_display(0, 0, HUB75_PANEL_WIDTH, 12, "Spark Zheng", 12, 0);
        apl_font_display(0, 12, HUB75_PANEL_WIDTH, 12, "Led Matrix", 12, 0);
        apl_font_display(0, 24, HUB75_PANEL_WIDTH, 16, "WellDone", 16, 0);
        apl_font_display(0, 40, HUB75_PANEL_WIDTH, 24, "Fight!", 24, 0);
      }
      sys_data.display_color = hub75_color;
      break;

    case KEY3_LONG:
      break;

    case KEY4_SHORT:
        menu_state = Menu_M;
        set_item = 1;
        apl_menu_m_display((set_item-1)/3);
      break;

    case KEY4_LONG:
      break;

    default:
      break;
  }
}

void apl_menu_2_display(uint8_t page)
{
  apl_font_display(0, 0, HUB75_PANEL_WIDTH, 16, "  COLOR ", 16, 0);
  //apl_led_matrix_write_str("  COLOR ", 0);
  if(page == 0)
  {
    apl_font_display(0, 16, HUB75_PANEL_WIDTH, 16, "1.Red   ", 16, 0);
    apl_font_display(0, 32, HUB75_PANEL_WIDTH, 16, "2.Green ", 16, 0);
    apl_font_display(0, 48, HUB75_PANEL_WIDTH, 16, "3.Yellow", 16, 0);
    apl_font_reverse(0, (set_item)*16, HUB75_PANEL_WIDTH, 16);
    //apl_led_matrix_write_str("1.Red   ", 1);
    //apl_led_matrix_write_str("2.Green ", 2);
    //apl_led_matrix_write_str("3.Yellow", 3);
    //apl_led_matrix_invert_row(set_item);
  }
  else if(page == 1)
  {
    apl_font_display(0, 16, HUB75_PANEL_WIDTH, 16, "4.Blue  ", 16, 0);
    apl_font_display(0, 32, HUB75_PANEL_WIDTH, 16, "5.Pink  ", 16, 0);
    apl_font_display(0, 48, HUB75_PANEL_WIDTH, 16, "6.Cyan  ", 16, 0);
    apl_font_reverse(0, (set_item-3)*16, HUB75_PANEL_WIDTH, 16);
    //apl_led_matrix_write_str("4.Blue  ", 1);
    //apl_led_matrix_write_str("5.Pink  ", 2);
    //apl_led_matrix_write_str("6.Cyan  ", 3);
    //apl_led_matrix_invert_row(set_item-3);
  }
  else if(page == 2)
  {
    apl_font_display(0, 16, HUB75_PANEL_WIDTH, 16, "7.White ", 16, 0);
    apl_font_display(0, 32, HUB75_PANEL_WIDTH, 16, "8.Auto  ", 16, 0);
    apl_font_display(0, 48, HUB75_PANEL_WIDTH, 16, "        ", 16, 0);
    apl_font_reverse(0, (set_item-6)*16, HUB75_PANEL_WIDTH, 16);
    //apl_led_matrix_write_str("7.White ", 1);
    //apl_led_matrix_write_str("8.Auto  ", 2);
    //apl_led_matrix_write_str("        ", 3);
    //apl_led_matrix_invert_row(set_item-6);
  }
}

