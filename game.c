/**
    @file game.c
    @author Isaac F, Cameron S, Vikas S
    @date October 2017
    @brief ENCE260 Game Assignment
*/


/* Included Modules */
#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "ledmat.h"
#include "../fonts/font5x7_1.h"
#include "ingame.h"
#include "pregame.h"
#include "display.h"
#include "userview.h"


/* Definitions */
#define PACER_RATE 500
#define MESSAGE_RATE 25


/* Initialise modules. */
void init(void)
{
    system_init ();
    navswitch_init ();
    ledmat_init ();
    ir_uart_init();
    pacer_init(PACER_RATE);
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    score1 = 0;
    score2 = 0;
}


/* Main Function */
int main(void)
{
    init();
    player = player_select();
    display_player(player);
    int direction = 0;
    while(1) {
        direction++;
        pacer_wait();
        tinygl_update();
        navswitch_update();
        startSpinner(direction);
    }
    return 0;
}
