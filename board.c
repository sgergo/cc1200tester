#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_nvic.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

#include "boardconfig.h"
#include "constants.h"
#include "uartstdio.h"
#include "board_spi.h"
#include "console.h"
#include "board_led.h"
#include "udma_config.h"


static uint32_t clockticksperus;
static uint32_t clockticksperms;
static uint32_t currtime = 0;



void board_fault(void) {
    ROM_GPIOPinWrite(LED_RED_PORTBASE, LED_RED, LED_RED);
}

static void board_configure_systemclock(void) {
    uint32_t clockfreq;
    // Set the clocking to run at 50 MHz from the PLL.
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);

    clockfreq = ROM_SysCtlClockGet();

    clockticksperus = (clockfreq / 1e6) / 3;
    clockticksperms = (clockfreq / 1e3) / 3;

}

static void board_delay_us(int us) {
    while (us--)
        ROM_SysCtlDelay(clockticksperus);
}

void board_delay_ms(int ms) {
    while (ms--)
        ROM_SysCtlDelay(clockticksperms);
}

static void board_enable_interrupts(void) {
    IntMasterEnable();
}

void board_reset(void) {
    HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;
}



void board_systick_isr(void) {
    // if (!(currtime++ % CC1200_CALLBACKPERIOD))
    //     com_cc1200_rtc_callback();  
}

void board_systick_init(void) {
    // Systick interrupt @ every 1 ms
    ROM_SysTickPeriodSet(ROM_SysCtlClockGet() / 1000);
    ROM_SysTickIntEnable();
    ROM_SysTickEnable();
}

void board_init(void) {

    // Configure clock
    board_configure_systemclock();

    // Configure uDMA
    udma_config_init();

    // Configure LEDs
#if (configUSE_LED == 1)
    board_configure_led();
#endif // configUSE_LED

    // Configure UART
#if (configUSE_CONSOLE_UART == 1)
    console_init();
#endif // configUSE_CONSOLE_UART

    // Configure SPI
#if (configUSE_SPI == 1)
    board_configure_spi();
#endif // configUSE_SPI

    // Configure SysTick timer
    board_systick_init();
    
    // Enable global interrupt
    board_enable_interrupts();
    
}
