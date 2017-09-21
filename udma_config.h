#ifndef UDMA_H
#define UDMA_H


void udma_config_transfer_spi(uint8_t *destbuffer, uint32_t transfersize);
void udma_config_transfer_memory_packet(uint8_t *srcbuffer, uint8_t *destbuffer, uint32_t transfersize);
void udma_config_init(void);

#endif
