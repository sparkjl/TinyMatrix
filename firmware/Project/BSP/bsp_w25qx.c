#include "includes.h"

uint8_t w25qx_buff[W25QX_SECTOR_SIZE];

uint8_t bsp_w25qx_read_id(uint8_t *p_id)
{
  uint8_t cmd[4] = {JEDEC_CMD_Device_ID, 0x00, 0x00, 0x00};
  uint8_t status = 1;

  W25QX_SPI_CS_L();
  status = HAL_SPI_Transmit(&hspi2, cmd, 4, W25QX_SPI_TIMEOUT);
  status = HAL_SPI_Receive(&hspi2, p_id, 2, W25QX_SPI_TIMEOUT);
  W25QX_SPI_CS_H();

  return status;
}

uint8_t bsp_w25qx_read(uint8_t *p_buff, uint32_t addr, uint16_t size)
{
  uint8_t cmd[4];
  uint8_t status = 1;

  cmd[0] = JEDEC_CMD_READ;
  cmd[1] = (uint8_t)(addr >> 16);
  cmd[2] = (uint8_t)(addr >> 8);
  cmd[3] = (uint8_t)(addr);

  W25QX_SPI_CS_L();
  status = HAL_SPI_Transmit(&hspi2, cmd, 4, W25QX_SPI_TIMEOUT);
  status = HAL_SPI_Receive(&hspi2, p_buff, size, W25QX_SPI_TIMEOUT);
  W25QX_SPI_CS_H();

  return status;
}

uint8_t bsp_w25qx_write_sector(uint8_t *p_buff, uint32_t addr, uint16_t size)
{
  uint8_t status = 1;
  uint16_t sector_number = 0;
  uint16_t sector_offset = 0;
  uint16_t sector_remain = 0;
  uint16_t i = 0;

  sector_number = (addr / W25QX_SECTOR_SIZE);
  sector_offset = (addr % W25QX_SECTOR_SIZE);
  sector_remain = W25QX_SECTOR_SIZE - sector_offset;

  if(size < sector_remain)
    sector_remain = size;

  while(1)
  {
    status = bsp_w25qx_read(w25qx_buff, sector_number*W25QX_SECTOR_SIZE, W25QX_SECTOR_SIZE);
    for(i=0; i<sector_remain; i++)
    {
      if(w25qx_buff[sector_offset+i] != 0xff)
        break; // need to be erased
    }
    if(i < sector_remain)
    {
      status = bsp_w25qx_erase_sector(sector_number);
      for(i=0; i<sector_remain; i++)
      {
        w25qx_buff[sector_offset+i] = p_buff[i];
      }
      status = bsp_w25qx_write_page(w25qx_buff, sector_number*W25QX_SECTOR_SIZE, W25QX_SECTOR_SIZE);
    }
    else
      status = bsp_w25qx_write_page(p_buff, addr, sector_remain);

    if(size == sector_remain)
      break; // write completed
    else
    {
      sector_number++;
      sector_offset = 0;

      p_buff += sector_remain;
      addr += sector_remain;
      size -= sector_remain; // deduct the bytes wrote
      if(size > W25QX_SECTOR_SIZE)
        sector_remain = W25QX_SECTOR_SIZE;
      else
        sector_remain = size;
    }
  }

  return status;
}

uint8_t bsp_w25qx_write_page(uint8_t *p_buff, uint32_t addr, uint16_t size)
{
  uint8_t status = 1;
  uint16_t page_remain = 0;

  page_remain = W25QX_PAGE_SIZE - (addr % W25QX_PAGE_SIZE); // single page remain bytes

  if(size <= page_remain)
    page_remain = size;

  while(1)
  {
    status = bsp_w25qx_write(p_buff, addr, page_remain);
    if(size == page_remain)
      break; // write completed
    else
    {
      p_buff += page_remain;
      addr += page_remain;
      size -= page_remain; // deduct the bytes wrote
      if(size > W25QX_PAGE_SIZE)
        page_remain = W25QX_PAGE_SIZE;
      else
        page_remain = size;
    }
  }

  return status;
}

uint8_t bsp_w25qx_write(uint8_t *p_buff, uint32_t addr, uint16_t size)
{
  uint8_t cmd[4];
  uint8_t status = 1;

  cmd[0] = JEDEC_CMD_PP;
  cmd[1] = (uint8_t)(addr >> 16);
  cmd[2] = (uint8_t)(addr >> 8);
  cmd[3] = (uint8_t)(addr);

  status = bsp_w25qx_write_enable();
  status = bsp_w25qx_wait_busy();
  W25QX_SPI_CS_L();
  status = HAL_SPI_Transmit(&hspi2, cmd, 4, W25QX_SPI_TIMEOUT);
  status = HAL_SPI_Transmit(&hspi2, p_buff, size, W25QX_SPI_TIMEOUT);
  W25QX_SPI_CS_H();
  status = bsp_w25qx_wait_busy();

  return status;
}

uint8_t bsp_w25qx_erase_sector(uint16_t sector)
{
  uint8_t cmd[4];
  uint8_t status = 1;

  cmd[0] = JEDEC_CMD_ERASE_4K;
  cmd[1] = (uint8_t)((sector*W25QX_SECTOR_SIZE) >> 16);
  cmd[2] = (uint8_t)((sector*W25QX_SECTOR_SIZE) >> 8);
  cmd[3] = (uint8_t)((sector*W25QX_SECTOR_SIZE));

  status = bsp_w25qx_write_enable();
  status = bsp_w25qx_wait_busy();
  W25QX_SPI_CS_L();
  status = HAL_SPI_Transmit(&hspi2, cmd, 4, W25QX_SPI_TIMEOUT);
  W25QX_SPI_CS_H();
  status = bsp_w25qx_wait_busy();

  return status;
}

uint8_t bsp_w25qx_erase_chip(void)
{
  uint8_t cmd = JEDEC_CMD_ERASE_full;
  uint8_t status = 1;

  status = bsp_w25qx_write_enable();
  status = bsp_w25qx_wait_busy();
  W25QX_SPI_CS_L();
  status = HAL_SPI_Transmit(&hspi2, &cmd, 1, W25QX_SPI_TIMEOUT);
  W25QX_SPI_CS_H();
  status = bsp_w25qx_wait_busy();

  return status;
}

static uint8_t bsp_w25qx_read_sr(uint8_t *p_sr)
{
  uint8_t cmd = JEDEC_CMD_RDSR1;
  uint8_t status = 1;

  W25QX_SPI_CS_L();
  status = HAL_SPI_Transmit(&hspi2, &cmd, 1, W25QX_SPI_TIMEOUT);
  status = HAL_SPI_Receive(&hspi2, p_sr, 1, W25QX_SPI_TIMEOUT);
  W25QX_SPI_CS_H();

  return status;
}

static uint8_t bsp_w25qx_write_sr(uint8_t *p_sr)
{
  uint8_t cmd[2] = {JEDEC_CMD_WSREN, JEDEC_CMD_WRSR};
  uint8_t status = 1;

  W25QX_SPI_CS_L();
  status = HAL_SPI_Transmit(&hspi2, cmd, 2, W25QX_SPI_TIMEOUT);
  status = HAL_SPI_Transmit(&hspi2, p_sr, 1, W25QX_SPI_TIMEOUT);
  W25QX_SPI_CS_H();

  return status;
}

static uint8_t bsp_w25qx_wait_busy(void)
{
  uint8_t sr = 0;
  uint8_t status = 1;
  uint32_t tickstart = HAL_GetTick();

  while(1)
  {
    if((HAL_GetTick() - tickstart) > W25QX_SPI_TIMEOUT)
      return 1;

    status = bsp_w25qx_read_sr(&sr);
    if((sr & 0x01) == 0x00)
      return status;
  }
}

static uint8_t bsp_w25qx_write_enable(void)
{
  uint8_t cmd = JEDEC_CMD_WREN;
  uint8_t status = 1;

  W25QX_SPI_CS_L();
  status = HAL_SPI_Transmit(&hspi2, &cmd, 1, W25QX_SPI_TIMEOUT);
  W25QX_SPI_CS_H();

  return status;
}

static uint8_t bsp_w25qx_write_disable(void)
{
  uint8_t cmd = JEDEC_CMD_WRDI;
  uint8_t status = 1;

  W25QX_SPI_CS_L();
  status = HAL_SPI_Transmit(&hspi2, &cmd, 1, W25QX_SPI_TIMEOUT);
  W25QX_SPI_CS_H();

  return status;
}

