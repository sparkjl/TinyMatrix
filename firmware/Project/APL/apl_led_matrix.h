#ifndef __APL_LED_MATRIX_H_
#define __APL_LED_MATRIX_H_

void apl_led_matrix_write_pixel(uint16_t x, uint16_t y, uint8_t color);
uint8_t apl_led_matrix_read_pixel(uint16_t x, uint16_t y);
void apl_led_matrix_left_shift(uint16_t y, uint16_t height, uint16_t count);

#endif /* __APL_LED_MATRIX_H_ */

