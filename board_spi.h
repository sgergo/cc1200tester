#ifndef BOARD_SPI_H
#define BOARD_SPI_H

void board_spi_assert_cs(void);
void board_spi_deassert_cs(void);
void board_spi_disable_udma(void);
void board_spi_enable_udma(void);
uint8_t board_spi_transfer_byte(uint8_t data);
void board_spi_udma_transfer(uint8_t *udmabuffer, uint32_t transfersize);
void board_configure_spi(void);

#endif // BOARD_SPI_H
