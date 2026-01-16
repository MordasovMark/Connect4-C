#include "logic.h"

// Check for a winning condition
int checkWin(Board* b, Cell player) {
    // Check Horizontal
    for (int row = 0; row < ROWS; row++) {
        // Loop stops at COLS - 3 to prevent out-of-bounds access
        for (int col = 0; col < COLS - 3; col++) {
            if (b->grid[row][col] == player &&
                b->grid[row][col + 1] == player &&
                b->grid[row][col + 2] == player &&
                b->grid[row][col + 3] == player)
                return 1;
        }
    }

    // Check Vertical
    // Loop stops at ROWS - 3 because we check downwards
    for (int row = 0; row < ROWS - 3; row++) {
        for (int col = 0; col < COLS; col++) {
            if (b->grid[row][col] == player &&
                b->grid[row + 1][col] == player &&
                b->grid[row + 2][col] == player &&
                b->grid[row + 3][col] == player)
                return 1;
        }
    }

    // Check Main Diagonal (\)
    for (int row = 0; row < ROWS - 3; row++) {
        for (int col = 0; col < COLS - 3; col++) {
            if (b->grid[row][col] == player &&
                b->grid[row + 1][col + 1] == player &&
                b->grid[row + 2][col + 2] == player &&
                b->grid[row + 3][col + 3] == player)
                return 1;
        }
    }

    // Check Secondary Diagonal (/)
    for (int row = 0; row < ROWS - 3; row++) {
        // Start from column 3 to allow checking backwards (leftwards)
        for (int col = 3; col < COLS; col++) {
            if (b->grid[row][col] == player &&
                b->grid[row + 1][col - 1] == player &&
                b->grid[row + 2][col - 2] == player &&
                b->grid[row + 3][col - 3] == player)
                return 1;
        }
    }

    return 0; // No win found
}

// Check for a draw (Board full)
int checkDraw(Board* b) {
    // We only need to check the top row.
    // If the top row is full, the entire board is full.
    for (int col = 0; col < COLS; col++) {
        if (b->grid[0][col] == EMPTY) 
            return 0; // Found an empty spot
    }
    return 1; // Top row is full
}