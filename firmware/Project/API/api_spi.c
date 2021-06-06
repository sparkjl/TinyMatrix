#include "includes.h"

void api_spi_init(void)
{
  SPI1_CS1_H();   //disable OMU M25P16
  SPI1_CS2_H();   //disable FRAM FM25CL64
  SPI1_CS3_H();   //disable MRAM MR25H256

  SPI2_CS0_H();   //disable ?  
  SPI2_CS1_H();   //disable EEPROM 25XX256
  SPI2_CS2_H();   //disable ?
  SPI2_CS3_H();   //disable EEPROM CAT25256

}

