#include <stdint.h>
// #include "types.h"
#include "constants.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"

#include "board.h"
#include "board_led.h"
#include "board_spi.h"

#include "console.h"
#include "command.h"
#include "cmdline.h"


// Convert string parameters to numbers
static int command_parse_numbers(int count, char *argv[], int numbase, long *store) {
    long num;
    char *endptr;
    int i;

    for (i = 0; i < (count - 1); i++) {
        errno = 0;
        num = strtol(argv[1 + i], &endptr, numbase);    
        if (*endptr != 0 || errno != 0) {
            console_printtext("ERROR: Invalid input.\n");
            return FAILURE;
        }
        
        *store++ = num;
    }

    return SUCCESS;
}

//
// A
//

//
// C
//

//
// D
//



//
// E
//


//
// G
//



//
//  H 
//
static int command_help(int argc, char *argv[]) {
    commandentry_t *entry;

    entry = &commandtable[0]; // Point at the beginning of the command table.

    console_printtext("\n");
    while(entry->commandname_ptr) {

        // Print the command name and the brief description.
        console_printtext("%s\t---\t%s\n", entry->commandname_ptr, entry->commandhelptext_ptr );
            
        // Advance to the next entry in the table. 
        entry++;
    }
    
    console_printtext("\n");
    return SUCCESS;
}

//
// I
//

//
// O
//


//
// R
//

static int command_reset(int argc, char *argv[]) {
    board_reset();
    return SUCCESS;
}


//
// P
//
// static int command_print_args(int argc, char *argv[]) {
//     long args[8];
//     int i;

//     if (argc < 2) {
//         console_printtext("ERROR: Missing argument(s).\n");
//         return FAILURE;
//     }

//     if (command_parse_numbers(argc, argv, 10, args) == FAILURE) {
//         console_printtext("ERROR: Something went wrong with the parsing.\n");
//         return FAILURE;
//     }

//     for (i = 0; i < (argc - 1); i++) {
//         console_printtext("STATUS: Arguments found: %d\n", args[i]);
//     }

//     return SUCCESS;
// }



//
// S
//


static int command_setup(int argc, char *argv[]) {

    
    return SUCCESS;
}



static int command_show_me(int argc, char *argv[]) {

    board_show_me();
    return SUCCESS;
}

//
// T
//




//
// U
//

void command_execute(char *commandline_received) {
    int ret;
    ret = cmdline_process(commandline_received);

    // If CmdLineProcess returns with a non-zero value something went wrong
    if (ret) 
        console_printtext("ERROR: Unknown command, error code: %d\n", ret); 
}



// Command table entries - fill it!
commandentry_t commandtable[] = {

    { "help", command_help,   "Display list of commands." },
    { "rst", command_reset,   "Reset unit." },
    { "seu", command_setup,   "Uploads setup byte sequence" },
    { "shm", command_show_me,   "Show me." },

    { 0, 0, 0} // Don't touch it, last entry must be a terminating NULL entry
};


