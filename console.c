#include <stdint.h>

#include "constants.h"
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

#include "boardconfig.h"
#include "console.h"
#include "command.h"
#include "uartstdio.h"
#include "board.h"


static void console_uart_init(uint32_t baudrate) {

    ROM_SysCtlPeripheralEnable(CONSOLEUARTPINPERIPHERIAL); // Enable the GPIO Peripheral used by the UART.
    ROM_GPIOPinConfigure(CONSOLEUARTRXPINTYPE); // Configure GPIO Pins for UART mode.
    ROM_GPIOPinConfigure(CONSOLEUARTTXPINTYPE);
    ROM_GPIOPinTypeUART(CONSOLEUARTPINPERIPHERIALBASE, CONSOLEUARTRXPIN | CONSOLEUARTTXPIN);

    uartstdio_config(0, baudrate, ROM_SysCtlClockGet()); // Initialize the UART for console I/O.

    uartstdio_flushrx();
    uartstdio_flushtx(true);
}

void console_init(void) {
	console_uart_init(CONSOLE_DEFAULT_BAUDRATE);

	
}

void console_printtext(const char *format , ...) {

	va_list arglist;
 	va_start( arglist, format );
 	uartstdio_vprintf( format, arglist );
 	va_end( arglist );
}


void console_read_uart_available_bytes(char *stdin_buffer, uint32_t *bytes_in) {	
	int f = uartstdio_peek('\r');
	if (f > -1) {
			*bytes_in = uartstdio_rxbytesavail();
			uartstdio_gets(stdin_buffer, *bytes_in);
			uartstdio_flushrx();
	} else
		*bytes_in = 0;		
}

void console_process(void) {
	static char stdin_buffer[STDINBUFFERSIZE];
	static uint32_t bytes_in;

	console_read_uart_available_bytes(stdin_buffer, &bytes_in);

	if (bytes_in > STDINDEFAULTCOMMANDSIZE)
		command_execute(stdin_buffer);
}
