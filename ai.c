#include "ai.h"
#include <stdlib.h>
#include "logic.h"

// Easy Bot: Selects a random valid column
int botEasy(Board* b) {
    int col;
    // Loop until a valid (non-full) column is found
    while (1) {
        col = rand() % COLS;
        // Check if the top row of the selected column is empty
        if (b->grid[0][col] == EMPTY) return col;
    }
}

// Medium Bot: Prioritizes center columns (Strategic positioning)
int botMedium(Board* b) {
    // Strategy: Center columns offer more winning connections
    // Order: 3(Center 2then alternating outwards
    int priorityOrder[] = { 3, 2, 4, 1, 5, 0, 6 };

    for (int i = 0; i < COLS; i++) {
        int targetCol = priorityOrder[i];

        // Validation check
        if (targetCol >= 0 && targetCol < COLS) {
       
            if (b->grid[0][targetCol] == EMPTY) {
                return targetCol;
            }
        }
    }

    // Fallback: If logic fails (shouldn't happen), play random
    return botEasy(b);
}