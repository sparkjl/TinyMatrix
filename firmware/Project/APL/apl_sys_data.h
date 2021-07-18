#ifndef __APL_SYS_DATA_H_
#define __APL_SYS_DATA_H_

#define SYS_PRODUCT_SN           "PAD20201220"          /* product SN number */
#define SYS_FIRMWARE_SN          "FAD20201220"          /* firmware SN number */
#define SYS_DATA_ADDR            0x00000000U            /* system data addr in spi flash */
#define SYS_FONT_ADDR            0x00200000U            /* system font addr in spi flash */

/* system data definition */
typedef struct
{
  uint32_t      check_code;
  uint32_t      initial_code;
  uint8_t       product_SN[40];
  uint8_t       firmware_SN[40];
  uint8_t       display_color;
  uint8_t       display_mode;
  uint8_t       display_language;
  uint8_t       font_size;
  uint8_t       font_text[6][64];
  uint8_t       reserved[548];            // 1024bytes in total

} System_DataTypeDef;

extern System_DataTypeDef  sys_data;

void apl_sys_data_read(void);
void apl_sys_data_write(void);
uint8_t apl_sys_data_changed(void);

#endif /* __APL_SYS_DATA_H_ */

