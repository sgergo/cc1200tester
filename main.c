#include <stdbool.h>
#include <stdint.h>
#include "constants.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"


#include "board.h"
#include "console.h"




int main(void) {


  board_init(); //mod: WDT disabled in board_init!

  // Print demo introduction.
  console_printtext("\nTM4C123 LaunchPad test application\n\n");


  while(1) {

      console_process();

      
  }

}
