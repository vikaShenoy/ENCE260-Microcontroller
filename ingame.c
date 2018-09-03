/**
    @file ingame.c
    @author Isaac Foster 64555890
    @date October 2017
    @brief ENCE260 Game Assignment
*/


#include "ingame.h"
#include "ir_uart.h"
#include "pacer.h"
#include "navswitch.h"
#include "ledmat.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "userview.h"
#include <stdlib.h>
#include "pregame.h"
#include "display.h"


#define SPEED 40


/* Display arrows for the four directions. */
static const uint8_t arrow[4][5] = {

    {0x00, 0x00, 0x1C, 0x00, 0x00},   //SOUTH
    {0x00, 0x00, 0x10, 0x10, 0x10},   //WEST
    {0x00, 0x00, 0x70, 0x00, 0x00},   //NORTH
    {0x10, 0x10, 0x10, 0x00, 0x00}    //EAST
};


/* Waits for a button push, and then starts the game. */
void startSpinner(int direction)
{


    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ir_uart_putc('s');
        direction = direction % 4;
        spinner(direction);
    }
    if (ir_uart_read_ready_p() && ir_uart_getc() == 's') {
        direction = direction % 4;
        spinner(direction);
    }

}


/* Waits for either player to correctly select the arrow direction.
 * Increments their score accordingly.
 * Returns the winner of the round. */
int findWinner(int direction, int player)
{
    while (1) {
        pacer_wait();
        navswitch_update();
        if (navswitch_push_event_p(direction)) {
            if (player == 1) {
                score1++;
                ir_uart_putc('1');
                return 1;
            } else { 
                score2++;
                ir_uart_putc('2');
                return 2;
            }
        }
        if (ir_uart_read_ready_p()) {
            if (ir_uart_getc() == '1') {
                score1++;
                return 1;
            } else {
                score2++;
                return 2;
            }
        }
    }
}


/* Creates the spinning pointer on the LED Matrix.
 * Stops in a random direction and waits for a nav push in this
 * direction.
 * Displays a winner when one player reaches 3 points, and resets
 * scores. */
void spinner (int dir)
{
    uint8_t column = 0;
    uint16_t timer = 0;
    uint16_t sSpeed;
    uint8_t lRow;
    int winner = 0;
    int i = 0;
    while (timer <= 7) {
        for(lRow = 0; lRow < 4; lRow++) {
            for (sSpeed = 0; sSpeed < SPEED; sSpeed++) {
                pacer_wait ();
                ledmat_display_column (arrow[lRow][column], column);
                column++;
                if (column > (LEDMAT_COLS_NUM - 1)) {
                    column = 0;
                }
            }
        }
        timer++;
    }

    for (i = 0; i < 5; i++) {
        for (sSpeed = 0; sSpeed < SPEED; sSpeed++) {
            pacer_wait ();
            ledmat_display_column(arrow[dir][column], column);
            column++;
            if (column > (LEDMAT_COLS_NUM - 1)) {
                column = 0;
            }
        }
    }
    
    winner = 0;
    winner = findWinner(dir, player);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    display_score(winner);
}
