#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "logic.h"
#include "ui.h"
#include "ai.h"

// Structure to hold separate statistics for PvP and PvC modes
typedef struct {
    // PvP Stats
    int pvp_p1Wins;
    int pvp_p2Wins;
    int pvp_draws;
    int pvp_total;

    // PvC Stats
    int pvc_playerWins;
    int pvc_aiWins;
    int pvc_draws;
    int pvc_total;
} GameStats;

void playPvP(GameStats* stats);
void playPvC(GameStats* stats);
void printStats(const GameStats* stats);

int main() {
    srand((unsigned int)time(NULL)); // Seed random number generator

    // Initialize all stats to zero
    GameStats currentStats = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int choice;

    while (1) {
        printMenu();

        // Input validation for menu selection
        if (scanf_s("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (choice == 1) {
            playPvP(&currentStats);
        }
        else if (choice == 2) {
            playPvC(&currentStats);
        }
        else if (choice == 3) {
            printStats(&currentStats);
        }
        else if (choice == 4) {
            printf("Bye bye\n");
            break;
        }
        else {
            printf("Invalid choice!\n");
            system("pause");
        }
    }

    return 0;
}

// Displays game statistics
void printStats(const GameStats* stats) {
    system("cls");
    printf("==================================\n");
    printf("         GAME STATISTICS          \n");
    printf("==================================\n\n");

    printf("--- Player vs Player (PvP) ---\n");
    printf(" Total Games:    %d\n", stats->pvp_total);
    printf(" P1 Wins:        %d\n", stats->pvp_p1Wins);
    printf(" P2 Wins:        %d\n", stats->pvp_p2Wins);
    printf(" Draws:          %d\n\n", stats->pvp_draws);

    printf("--- Player vs Computer (PvC) ---\n");
    printf(" Total Games:    %d\n", stats->pvc_total);
    printf(" Player Wins:    %d\n", stats->pvc_playerWins);
    printf(" Computer Wins:  %d\n", stats->pvc_aiWins);
    printf(" Draws:          %d\n", stats->pvc_draws);

    printf("==================================\n");
    system("pause");
}

// Handles Player vs Player game logic
void playPvP(GameStats* stats) {
    Board board;
    initBoard(&board);
    Cell currentPlayer = PLAYER1;
    int col;

    while (1) {
        printBoardColored(&board);
        printf("Player %d, choose column (1-7): ", currentPlayer);

        // Input validation
        if (scanf_s("%d", &col) != 1) {
            while (getchar() != '\n');
            continue;
        }

        int actualCol = col - 1; // Convert to 0-based index

        // Check bounds
        if (actualCol < 0 || actualCol >= COLS) {
            printf("Invalid column! Please choose 1-7.\n");
            system("pause");
            continue;
        }

        // Check if column is full (Top row check)
        if (board.grid[0][actualCol] != EMPTY) {
            printf("Column is full!\n");
            system("pause");
            continue;
        }

        // Visualize drop and update logic
        animateDrop(&board, actualCol, currentPlayer);

        // Check for Win
        if (checkWin(&board, currentPlayer)) {
            printf("Player %d WINS!\n", currentPlayer);

            stats->pvp_total++;
            if (currentPlayer == PLAYER1) stats->pvp_p1Wins++;
            else stats->pvp_p2Wins++;

            system("pause");
            break;
        }

        // Check for Draw
        if (checkDraw(&board)) {
            printf("Game ends in a DRAW!\n");
            stats->pvp_total++;
            stats->pvp_draws++;
            system("pause");
            break;
        }

        // Switch turn
        if (currentPlayer == PLAYER1) currentPlayer = PLAYER2;
        else currentPlayer = PLAYER1;
    }
}

// Handles Player vs Computer game logic
void playPvC(GameStats* stats) {
    Board board;
    initBoard(&board);
    Cell currentPlayer = PLAYER1;
    int difficulty = printDifficultyMenu();
    int col;

    while (1) {
        printBoardColored(&board);

        // Human Turn 
        if (currentPlayer == PLAYER1) {
            printf("Player, choose column (1-7): ");

            if (scanf_s("%d", &col) != 1) {
                while (getchar() != '\n');
                continue;
            }

            int actualCol = col - 1;

            if (actualCol < 0 || actualCol >= COLS) {
                printf("Invalid column! Choose 1-7.\n");
                system("pause");
                continue;
            }

            if (board.grid[0][actualCol] != EMPTY) {
                printf("Column is full!\n");
                system("pause");
                continue;
            }

            animateDrop(&board, actualCol, currentPlayer);
        }
        //  Computer Turn 
        else {
            printf("Computer is thinking...\n");
            Sleep(500); // Simulate thinking time

            // Get AI move based on difficulty
            if (difficulty == 1) col = botEasy(&board);
            else col = botMedium(&board);

            // Fallback for AI safety (prevent crash on full column)
            if (board.grid[0][col] != EMPTY) {
                for (int i = 0; i < COLS; i++) {
                    if (board.grid[0][i] == EMPTY) 
                    { 
                        col = i; break;
                    }
                }
            }

            printf("Computer chooses column %d\n", col + 1);
            animateDrop(&board, col, currentPlayer);
        }

        // Check Game Over conditions
        if (checkWin(&board, currentPlayer)) {
            if (currentPlayer == PLAYER1) {
                printf("\n>>> PLAYER WINS! <<<\n");
                stats->pvc_playerWins++;
            }
            else {
                printf("\n>>> COMPUTER WINS! <<<\n");
                stats->pvc_aiWins++;
            }
            stats->pvc_total++;
            system("pause");
            break;
        }

        if (checkDraw(&board)) {
            printf("\nIt's a DRAW!\n");
            stats->pvc_total++;
            stats->pvc_draws++;
            system("pause");
            break;
        }

        // Switch turn
        if (currentPlayer == PLAYER1) currentPlayer = PLAYER2;
        else currentPlayer = PLAYER1;
    }
}