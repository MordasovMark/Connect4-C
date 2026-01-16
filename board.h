#ifndef BOARD_H
#define BOARD_H

#define ROWS 6
#define COLS 7

// Enum representing the state of a single cell
typedef enum {
    EMPTY = 0,   // Empty slot
    PLAYER1 = 1, // Player 1 (or Human)
    PLAYER2 = 2  // Player 2 (or AI)
} Cell;

// Structure representing the game board
typedef struct {
    Cell grid[ROWS][COLS]; // 2D array storing the board state
} Board;

// Initializes the board (sets all cells to EMPTY)
void initBoard(Board* b);

// Prints a basic text representation of the board (Debug/Console)
void printBoard(Board* b);

// Drops a token into the specified column (simulates gravity)
// Returns the row index where the token landed, or -1 if column is full
int dropToken(Board* b, int col, Cell player);

#endif