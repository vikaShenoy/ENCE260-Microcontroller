/**
    @file ingame.h
    @author Isaac Foster 64555890
    @date October 2017
    @brief ENCE260 Game Assignment
*/


#ifndef INGAME_H
#define INGAME_H


/* Globals */
int player;


/* Declarations. */
void spinner (int dir);
void startSpinner(int direction);
int findWinner(int direction, int player);


#endif
