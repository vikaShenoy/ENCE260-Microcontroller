/**
    @file userview.c
    @author Vikas Shenoy
    @date October 2017
    @brief ENCE260 Game Assignment
*/


#include "display.h"
#include "pio.h"
#include "system.h"
#include "tinygl.h"
#include "userview.h"
#include "font.h"
#include "ledmat.h"
#include "pacer.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"
#include "ingame.h"
#include "pregame.h"


#define LOOP_RATE 1000


/* Scrolls the correct player num on each LED matrix. */
void display_player(int player)
{
    char * playerNum[3];
    if (player == 1) {
        playerNum[0] = "P1\0";
    } else {
        playerNum[0] = "P2\0";
    }
    tinygl_text(*playerNum);
}


/* Scrolls a start message on the screen before player select. */
void display_start(void)
{

    tinygl_text("Press Start");
    tinygl_update();
}


/* Displays a W or L on each LED screen.
 * Displays winner/loser when one person reaches 3, and resets score. */
void display_score(int winner) 
{
    if (winner == 1) {
        if (player == 1) {
            tinygl_text("W");
        } else {
            tinygl_text("L");
        }
    } else {
        if (player == 2) {
            tinygl_text("W");
        } else {
            tinygl_text("L");
        }
    }
    
    if (score1 == 3) {
        score1 = 0;
        score2 = 0;
        if (player == 1) {
            tinygl_text("Winner");
        } else { 
            tinygl_text("Loser");
        }
    } 
    
    if (score2 == 3) {
        score1 = 0;
        score2 = 0;
        if (player == 2) {
            tinygl_text("Winner");
        } else { 
            tinygl_text("Loser");
        }
    }
    tinygl_update();
}
