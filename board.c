#include "board.h"
#include <stdio.h>

// Initializes the board by setting all cells to EMPTY
void initBoard(Board* b) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            b->grid[row][col] = EMPTY;
        }
    }
}

// Prints a simple text-based representation of the board (Debug purposes)
void printBoard(Board* b) {
    for (int row = 0; row < ROWS; row++) {
        printf("|");
        for (int col = 0; col < COLS; col++) {
            char c = ' ';
            if (b->grid[row][col] == PLAYER1) c = 'O';
            else if (b->grid[row][col] == PLAYER2) c = 'O';
            printf("%c|", c);
        }
        printf("\n");
    }
}

// Drops a token into a specific column (Simulates gravity)
int dropToken(Board* b, int col, Cell player) {
    // Boundary check
    if (col < 0 || col >= COLS) return -1;

    // Iterate from bottom (ROWS-1) to top (0) to find the first empty slot
    for (int row = ROWS - 1; row >= 0; row--) {
        if (b->grid[row][col] == EMPTY) {
            b->grid[row][col] = player;
            return 0; // Success
        }
    }
    return -1; // Column is full
}