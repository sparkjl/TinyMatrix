#ifndef __API_SYS_H_
#define __API_SYS_H_


#define delay_ms(x)     HAL_Delay(x)
/* iar delay */
#define CPU_F           (double)(72000000u)              //MCLK:72MHZ
//#define delay_us(x)     __delay_cycles((unsigned long)(CPU_F * (double)x / 1000000.0))
//#define delay_ms(x)     __delay_cycles((unsigned long)(CPU_F * (double)x / 1000.0))
void delay_us(uint32_t n_us);


#endif /* __API_SYS_H_ */

