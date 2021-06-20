#ifndef __APL_KEY_MENU_H_
#define __APL_KEY_MENU_H_

typedef enum
{
  Menu_R,

  Menu_M,
  Menu_1,
  Menu_2,
  Menu_3,

} Menu_StateTypeDef;

static Menu_StateTypeDef menu_state;
static uint8_t menu_item;
static uint8_t key_value;

void apl_menu_init(void);
void apl_menu_handle(void);
void apl_menu_r_callback(void);
void apl_menu_r_display(uint8_t page);
void apl_menu_m_callback(void);
void apl_menu_m_display(uint8_t page);
void apl_menu_1_callback(void);
void apl_menu_1_display(uint8_t page);
void apl_menu_2_callback(void);
void apl_menu_2_display(uint8_t page);

#endif /* __APL_KEY_MENU_H_ */

