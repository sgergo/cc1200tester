#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ssi.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"
#include "driverlib/udma.h"
#include "driverlib/interrupt.h"
#include "driverlib/udma.h"

#include "boardconfig.h"
#include "constants.h"

static uint8_t udma_controltable[1024] __attribute__ ((aligned(1024)));

void udma_config_transfer_spi(uint8_t *destbuffer, uint32_t transfersize) {
    static uint32_t dummy = 0xaaaaaaaa; // 4 dummy bytes
    // static uint32_t dummy = 0xff; // 1 dummy byte

    // uDMAChannelDisable(SPIUDMATXCHANNEL); // Deactivate TX channel
    // uDMAChannelDisable(SPIUDMARXCHANNEL); // Deactivate RX channel
    // uDMAChannelControlSet(SPIUDMATXCHANNEL, UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_NONE | UDMA_ARB_1);
    // uDMAChannelControlSet(SPIUDMARXCHANNEL, UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 | UDMA_ARB_1);

    uDMAChannelTransferSet (SPIUDMATXCHANNEL, UDMA_MODE_BASIC, 
                            (void *)&dummy, 
                            (void*)(SPIPERIPHERIALBASE + SSI_O_DR), 
                            transfersize);
    uDMAChannelTransferSet(SPIUDMARXCHANNEL, UDMA_MODE_BASIC, 
                            (void*)(SPIPERIPHERIALBASE + SSI_O_DR), 
                            (void*)destbuffer, 
                            transfersize);

    uDMAChannelEnable(SPIUDMARXCHANNEL); // Activate RX channel
    uDMAChannelEnable(SPIUDMATXCHANNEL); // Activate TX channel

    // We need this?
    IntEnable(SPIPERIPHERIALINT);
}

void udma_config_transfer_memory_packet(uint8_t *srcbuffer, uint8_t *destbuffer, uint32_t transfersize) {
	ROM_uDMAChannelTransferSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT,
									UDMA_MODE_AUTO, srcbuffer, destbuffer,
									transfersize);

	ROM_uDMAChannelEnable (UDMA_CHANNEL_SW);
	ROM_uDMAChannelRequest(UDMA_CHANNEL_SW);
}

static void udma_config_configure_udma_channels(void) {

	// SPI -> packetmemory uDMA
	ROM_uDMAChannelAttributeDisable(SPIUDMARXCHANNEL,
                                    UDMA_ATTR_USEBURST | 
                                    (UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK));

    ROM_uDMAChannelAttributeDisable(SPIUDMATXCHANNEL,
                                    UDMA_ATTR_USEBURST | 
                                    (UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK));

    uDMAChannelControlSet(SPIUDMATXCHANNEL, UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_NONE | UDMA_ARB_1);
    uDMAChannelControlSet(SPIUDMARXCHANNEL, UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 | UDMA_ARB_1);

    // packetmemory -> packetbuffer uDMA
	// ROM_uDMAChannelAttributeDisable(UDMA_CHANNEL_SW,
	// 								UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT |
	// 								(UDMA_ATTR_HIGH_PRIORITY |
	// 								UDMA_ATTR_REQMASK));

 //    ROM_uDMAChannelControlSet(UDMA_CHANNEL_SW | UDMA_PRI_SELECT,
	// 								UDMA_SIZE_8 | UDMA_SRC_INC_8 | UDMA_DST_INC_8 |
	// 								UDMA_ARB_1);

}

void udma_config_init(void) {
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    ROM_uDMAEnable();
    ROM_uDMAControlBaseSet(udma_controltable);
    udma_config_configure_udma_channels();
}




