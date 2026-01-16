#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "ui.h"
#include "board.h"

// Helper function to change console text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Displays difficulty selection and validates input
int printDifficultyMenu() {
    int choice = 0;

    printf("\n");
    setColor(14); // Yellow title
    printf("Select Difficulty:\n");
    setColor(7);  // White text
    printf("1. Easy (Random moves)\n");
    printf("2. Medium (Basic logic)\n");
    printf("Choose (1-2): ");

    // Input validation loop
    while (scanf_s("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        while (getchar() != '\n'); // Clear input buffer
        printf("Invalid choice! Try again (1-2): ");
    }

    return choice;
}

// Displays the main game menu
void printMenu() {
    system("cls");
    setColor(11); // Cyan border
    printf("+=======================+\n");
    printf("|     CONNECT FOUR      |\n");
    printf("+=======================+\n");
    printf("| 1. Player vs Player   |\n");
    printf("| 2. Player vs Computer |\n");
    printf("| 3. Game Statistics    |\n");
    printf("| 4. Exit               |\n");
    printf("+=======================+\n");
    setColor(7); // Reset to white
    printf("Choose option: ");
}

// Renders the game board with colors
void printBoardColored(Board* b) {
    system("cls"); // Clear screen for fresh render

    setColor(14);
    printf("\n    CONNECT FOUR\n\n");

    for (int i = 0; i < ROWS; i++) {
        setColor(9); // Blue borders
        printf("   |");

        for (int j = 0; j < COLS; j++) {
            if (b->grid[i][j] == PLAYER1) {
                setColor(12); // Red for Player 1
                printf(" O ");
            }
            else if (b->grid[i][j] == PLAYER2) {
                setColor(14); // Yellow for Player 2
                printf(" O ");
            }
            else {
                setColor(8); // Grey for empty slots
                printf(" . ");
            }

            setColor(9); // Blue separator
            printf("|");
        }
        printf("\n");
    }

    // Bottom border
    setColor(9);
    printf("   +");
    for (int j = 0; j < COLS; j++) printf("---+");
    printf("\n");

    // Column numbers
    setColor(15);
    printf("    ");
    for (int j = 0; j < COLS; j++) printf(" %d  ", j + 1);
    printf("\n\n");

    setColor(7); // Reset color
}

// Animates a token falling into a specific column
void animateDrop(Board* b, int col, Cell player) {
    // Calculate the final landing row
    int targetRow = -1;
    for (int r = ROWS - 1; r >= 0; r--) {
        if (b->grid[r][col] == EMPTY) {
            targetRow = r;
            break;
        }
    }

    // If column is full, do nothing
    if (targetRow == -1) return;

    // Animation loop: drop token row by row
    for (int row = 0; row <= targetRow; row++) {
        b->grid[row][col] = player; // Draw token
        printBoardColored(b);
        Sleep(50); // Short delay for animation effect

        b->grid[row][col] = EMPTY; // Erase token for next step
    }

    // Finalize the move in the logic board
    dropToken(b, col, player);
    printBoardColored(b);
}