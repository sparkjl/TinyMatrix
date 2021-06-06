#ifndef __BSP_KEY_H_
#define __BSP_KEY_H_

/* key interface definition */
#define KEY_SHORT_COUNT            (uint8_t)(3u)
#define KEY_LONG_COUNT             (uint8_t)(30u)

/* key handler definition */
typedef struct
{
  uint8_t      key1;                  /* key1 count */
  uint8_t      key2;                  /* key2 count */
  uint8_t      key3;                  /* key3 count */
  uint8_t      key4;                  /* key4 count */

} Key_HandleTypeDef;

typedef enum
{
  KEY1_SHORT   = 0x01U,
  KEY1_LONG    = 0x03U,
  KEY2_SHORT   = 0x11U,
  KEY2_LONG    = 0x13U,
  KEY3_SHORT   = 0x21U,
  KEY3_LONG    = 0x23U,
  KEY4_SHORT   = 0x31U,
  KEY4_LONG    = 0x33U

} Key_ValueTypeDef;

static Key_HandleTypeDef      key;

void bsp_key_scan(void);
uint8_t bsp_key_read(void);

#endif /* __BSP_KEY_H_ */

