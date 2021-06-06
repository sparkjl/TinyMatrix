#ifndef __BSP_W25QX_H_
#define __BSP_W25QX_H_

/* w25qx definition */
#define W25QX_PAGE_SIZE                 (256u)                          // Page Size:   256 bytes
#define W25QX_SECTOR_SIZE               (W25QX_PAGE_SIZE *  16u)        // Sector Size: 4  Kbytes
#define W25QX_BLOCK_SIZE                (W25QX_PAGE_SIZE * 256u)        // Block Size:  64 Kbytes
#define W25QX_DEVICE_ID                 (0xEF)                          // Winbond
#define W25QX_JEDEC_ID                  (0x4018)                        // Manufacturer ID/Device ID/Memory Type (ID15-ID8)/Capacity (ID7-ID0)

/* JEDEC definition */
#define JEDEC_CMD_WRSR                  (0x01)                          // Write Status Register
#define JEDEC_CMD_PP                    (0x02)                          // Page Program
#define JEDEC_CMD_READ                  (0x03)                          // Read Data
#define JEDEC_CMD_WRDI                  (0x04)                          // Write Disable
#define JEDEC_CMD_RDSR1                 (0x05)                          // Read Status Register-1
#define JEDEC_CMD_WREN                  (0x06)                          // Write Enable
#define JEDEC_CMD_FAST_READ             (0x0B)                          // Fast Read
#define JEDEC_CMD_ERASE_4K              (0x20)                          // 4KB Sector Erase
#define JEDEC_CMD_RDSR2                 (0x35)                          // Read Status Register-2
#define JEDEC_CMD_WSREN                 (0x50)                          // Volatile SR Write Enable
#define JEDEC_CMD_ERASE_32K             (0x52)                          // 32KB Black Erase
#define JEDEC_CMD_Device_ID             (0x90)                          // Read Device ID
#define JEDEC_CMD_JEDEC_ID              (0x9F)                          // Read JEDEC ID
#define JEDEC_CMD_ERASE_full            (0xC7)                          // Chip Erase
#define JEDEC_CMD_ERASE_64K             (0xD8)                          // 64KB Block Erase

#define W25QX_SPI_TIMEOUT               (100u)
#define W25QX_SPI_CS_H()                SPI2_CS0_H()
#define W25QX_SPI_CS_L()                SPI2_CS0_L()

extern SPI_HandleTypeDef hspi2;

uint8_t bsp_w25qx_read_id(uint8_t *p_id);
uint8_t bsp_w25qx_read(uint8_t *p_buff, uint32_t addr, uint16_t size);
uint8_t bsp_w25qx_write_sector(uint8_t *p_buff, uint32_t addr, uint16_t size);
uint8_t bsp_w25qx_write_page(uint8_t *p_buff, uint32_t addr, uint16_t size);
uint8_t bsp_w25qx_write(uint8_t *p_buff, uint32_t addr, uint16_t size);
uint8_t bsp_w25qx_erase_sector(uint16_t sector);
uint8_t bsp_w25qx_erase_chip(void);
static uint8_t bsp_w25qx_read_sr(uint8_t *p_sr);
static uint8_t bsp_w25qx_write_sr(uint8_t *p_sr);
static uint8_t bsp_w25qx_wait_busy(void);
static uint8_t bsp_w25qx_write_enable(void);
static uint8_t bsp_w25qx_write_disable(void);

#endif /* __BSP_W25QX_H_ */

