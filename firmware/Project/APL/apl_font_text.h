#ifndef __FONT_H_
#define __FONT_H_

#define HZ_FONT_SIZE_0            0x0008D000U                          /* song12 font size:   577,536 bytes */
#define HZ_FONT_SIZE_1            0x000BC000U                          /* song16 font size:   770,048 bytes */
#define HZ_FONT_SIZE_2            0x001A5000U                          /* song24 font size: 1,724,416 bytes */

#define HZ_FONT_ADDR_0            SYS_FONT_ADDR                        /* song12 font addr in spi flash */
#define HZ_FONT_ADDR_1            HZ_FONT_ADDR_0 + HZ_FONT_SIZE_0      /* song16 font addr in spi flash */
#define HZ_FONT_ADDR_2            HZ_FONT_ADDR_1 + HZ_FONT_SIZE_1      /* song24 font addr in spi flash */
#define HZ_FONT_ADDR_END          HZ_FONT_ADDR_2 + HZ_FONT_SIZE_2      /* end font addr in spi flash */


#define ASCII_FONT_STYLE

//extern unsigned char ascii_1206[95][12];
//extern unsigned char ascii_1608[95][16];
//extern unsigned char ascii_2412[95][36];

extern uint32_t font_size;
extern uint8_t  font_mode;
extern uint8_t  font_buff[256];

/* rolling display handler definition */
typedef struct
{
  uint16_t      x_dis;
  uint16_t      offset;
  uint16_t      p_dev;

} Roll_DisplayTypeDef;

extern Roll_DisplayTypeDef roll[16];

uint8_t apl_font_erase(uint8_t index);
void apl_font_upgrade(uint8_t *p_buff, uint16_t size);

void apl_font_init(void);
void apl_font_display_char(uint16_t x, uint16_t y, uint8_t ch, uint8_t size, uint8_t mode);
void apl_font_display_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *p_str, uint8_t size);
void apl_font_gethz(uint8_t *p_hz, uint8_t *p_data, uint8_t size);
void apl_font_display_hz(uint16_t x, uint16_t y, uint8_t *p_hz, uint8_t size, uint8_t mode);
void apl_font_display(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t *p_str, uint8_t size, uint8_t mode);
void apl_font_rolling(uint16_t y, uint8_t *p_str, uint8_t size, Roll_DisplayTypeDef *p_roll);
void apl_font_reverse(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

#endif

