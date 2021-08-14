#include "includes.h"

void api_spi_init(void)
{
  SPI1_CS1_H();
  SPI1_CS2_H();
  SPI1_CS3_H();

  SPI2_CS0_H();
  SPI2_CS1_H();
  SPI2_CS2_H();
  SPI2_CS3_H();

}

