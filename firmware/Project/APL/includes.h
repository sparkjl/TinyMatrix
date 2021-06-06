#ifndef __INCLUDES_H_
#define __INCLUDES_H_

#include <stdlib.h>
#include <string.h>

#include "stm32f1xx_hal.h"
//#include "stm32f2xx_hal.h"
//#include "stm32f4xx_hal.h"

/* APL Layer -----------------------------------------------------------------*/
#include "main.h"
#include "apl_task.h"
#include "apl_sys_data.h"
#include "apl_uart_link.h"
#include "apl_key_menu.h"
#include "apl_led_matrix.h"
#include "apl_font_text.h"

/* BSP Layer -----------------------------------------------------------------*/
#include "bsp_hub75.h"
#include "bsp_w25qx.h"
#include "bsp_key.h"

/* API Layer -----------------------------------------------------------------*/
#include "api_sys.h"
#include "api_task.h"
#include "api_gpio.h"
#include "api_uart.h"
#include "api_spi.h"
#include "api_tim.h"

#endif /* __INCLUDES_H_ */

