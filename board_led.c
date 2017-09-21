#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"


#include "boardconfig.h"
#include "constants.h"
#include "board.h"

#define LEDOUT       (*((volatile uint32_t *)0x400253FC))

void board_configure_led(void) {
	ROM_SysCtlPeripheralEnable(LED_ALL_PINPERIPHERIAL);
    ROM_GPIOPinTypeGPIOOutput(LED_ALL_PORTBASE, LED_RED|LED_BLUE|LED_GREEN);
    ROM_GPIOPinWrite(LED_ALL_PORTBASE, LED_RED|LED_GREEN|LED_BLUE, 0); // Switch off all LEDs
}

static void board_red_led_on(void) {
    ROM_GPIOPinWrite(LED_ALL_PORTBASE, LED_RED, LED_RED); 
}

static void board_red_led_off(void) {
    ROM_GPIOPinWrite(LED_ALL_PORTBASE, LED_RED, 0); 
}

static void board_blue_led_on(void) {
    ROM_GPIOPinWrite(LED_ALL_PORTBASE, LED_BLUE, LED_BLUE); 
}

static void board_blue_led_off(void) {
    ROM_GPIOPinWrite(LED_ALL_PORTBASE, LED_BLUE, 0); 
}

void board_green_led_on(void) {
    ROM_GPIOPinWrite(LED_ALL_PORTBASE, LED_GREEN, LED_GREEN); 
}

void board_green_led_off(void) {
    ROM_GPIOPinWrite(LED_ALL_PORTBASE, LED_GREEN, 0); 
}

void board_toggle_green_led(void) {
	LEDOUT ^=LED_GREEN;
}

void board_blink_red_led(void) {
	board_red_led_on();
	board_delay_ms(LEDBLINKINMS);
	board_red_led_off();
}

void board_blink_blue_led(void) {
	board_blue_led_on();
	board_delay_ms(LEDBLINKINMS);
	board_blue_led_off();
}

void board_blink_green_led(void) {
	board_green_led_on();
	board_delay_ms(LEDBLINKINMS);
	board_green_led_off();
}

void board_show_me(void) {
	board_blink_blue_led();
	board_delay_ms(LEDBLINKINMS);
	board_blink_red_led();
	board_delay_ms(LEDBLINKINMS);
	board_blink_green_led();
}

