#ifndef LOGIC_H
#define LOGIC_H

#include "board.h"

// Checks if a specific player has won
int checkWin(Board* b, Cell player);

// Checks for a draw (full board)
int checkDraw(Board* b);

#endif