/**
    @file pregame.c
    @author Cameron Shellard
    @date October 2017
    @brief ENCE260 Game Assignment
*/


#include "userview.h"
#include "pacer.h"
#include "navswitch.h"
#include "display.h"
#include "system.h"
#include "pio.h"
#include "ledmat.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "ingame.h"
#include "pregame.h"



/* Selects player1 and player2. */
int player_select(void)
{
    ir_uart_init();
    display_start();
    while (1) {
        tinygl_update();
        if (ir_uart_read_ready_p()) {
            if (ir_uart_getc() == 'c') {
                tinygl_clear();
                tinygl_update();
                return 2;
            }
        }
        navswitch_update ();

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc('c');
            tinygl_clear();
            tinygl_update();
            return 1;
        }
        pacer_wait();

    }
    return 2;
}
