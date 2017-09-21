/*
 * cc1200registers.c
 *
 *  Created on: Sep 21, 2017
 *      Author: gsantha
 */

#include "libcc1200.h"

cc1200_register_field_t regs[] = {
     {.reg = CC1200_SYNC_CFG1, .value = 0xaa},
     {.reg = CC1200_SYNC3, .value = 0xd3},
     {.reg = CC1200_SYNC2, .value = 0x91},
     {.reg = CC1200_SYNC1, .value = 0xd3},
     {.reg = CC1200_SYNC0, .value = 0x91},
     {.reg = CC1200_PREAMBLE_CFG1, .value = 0x18},
     {.reg = CC1200_IOCFG0, .value = 0x06},
     {.reg = CC1200_IOCFG2, .value = 0x00},
     {.reg = CC1200_MODCFG_DEV_E, .value = 0x03},
     {.reg = CC1200_PREAMBLE_CFG0, .value = 0x8f},
     {.reg = CC1200_IQIC, .value = 0xc8},
     {.reg = CC1200_CHAN_BW, .value = 0x10},
     {.reg = CC1200_MDMCFG1, .value = 0x42},
     {.reg = CC1200_MDMCFG0, .value = 0x05},
     {.reg = CC1200_SYMBOL_RATE2, .value = 0x8f},
     {.reg = CC1200_SYMBOL_RATE1, .value = 0x75},
     {.reg = CC1200_SYMBOL_RATE0, .value = 0x10},
     {.reg = CC1200_AGC_REF, .value = 0x27},
     {.reg = CC1200_AGC_CS_THR, .value = 0xee},
     {.reg = CC1200_AGC_CFG1, .value = 0x11},
     {.reg = CC1200_AGC_CFG0, .value = 0x94},
     {.reg = CC1200_FIFO_CFG, .value = 0xbe},
     {.reg = CC1200_DEV_ADDR, .value = 0x00},
     {.reg = CC1200_FS_CFG, .value = 0x14},
     {.reg = CC1200_PKT_CFG2, .value = 0x00},
     {.reg = CC1200_PKT_CFG1, .value = 0x1b},
     {.reg = CC1200_PKT_CFG0, .value = 0x00},
     {.reg = CC1200_PA_CFG1, .value = 0x7f},

     // Terminal entry
     {.reg = 0x00, .value = 0x00}
};

cc1200_register_field_t extregs[] = {
     {.reg = CC1200_EXT_IF_MIX_CFG, .value = 0x1c},
     {.reg = CC1200_EXT_TOC_CFG, .value = 0x03},
     {.reg = CC1200_EXT_MDMCFG2, .value = 0x02},
     {.reg = CC1200_EXT_FREQ2, .value = 0x56},
     {.reg = CC1200_EXT_FREQ1, .value = 0x9e},
     {.reg = CC1200_EXT_FREQ0, .value = 0xb8},
     {.reg = CC1200_EXT_IF_ADC1, .value = 0xee},
     {.reg = CC1200_EXT_IF_ADC0, .value = 0x10},
     {.reg = CC1200_EXT_FS_DIG1, .value = 0x04},
     {.reg = CC1200_EXT_FS_DIG0, .value = 0x50},
     {.reg = CC1200_EXT_FS_CAL1, .value = 0x40},
     {.reg = CC1200_EXT_FS_CAL0, .value = 0x0e},
     {.reg = CC1200_EXT_FS_DIVTWO, .value = 0x03},
     {.reg = CC1200_EXT_FS_DSM0, .value = 0x33},
     {.reg = CC1200_EXT_FS_DVC1, .value = 0xf7},
     {.reg = CC1200_EXT_FS_DVC0, .value = 0x0f},
     {.reg = CC1200_EXT_FS_PFD, .value = 0x00},
     {.reg = CC1200_EXT_FS_PRE, .value = 0x6e},
     {.reg = CC1200_EXT_FS_REG_DIV_CML, .value = 0x1c},
     {.reg = CC1200_EXT_FS_SPARE, .value = 0xac},
     {.reg = CC1200_EXT_FS_VCO0, .value = 0xb5},
     {.reg = CC1200_EXT_IFAMP, .value = 0x09},
     {.reg = CC1200_EXT_XOSC5, .value = 0x0e},
     {.reg = CC1200_EXT_XOSC1, .value = 0x03},

     // Terminal entry
     {.reg = 0x00, .value = 0x00}
};


