#ifndef UI_H
#define UI_H

#include "board.h"

// Main menu
void printMenu();

// Prints a colored board
void printBoardColored(Board* b);

// Animation of a falling disc
void animateDrop(Board* b, int col, Cell player);

// Difficulty level selection menu
int printDifficultyMenu();

#endif