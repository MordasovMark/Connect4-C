# Connect4-C
### Advanced Connect 4 implementation in C language featuring minimax AI and modular architecture

## Project Overview
this project is a full implementation of the classic connect 4 game written in c where players can compete against each other or against a smart ai agent the game is built with a clear separation between logic user interface and game management to ensure clean code and easy maintenance 

## System Architecture
the project is divided into several key modules each responsible for a specific domain of the game logic 
* **ai.c/h**: contains the decision making algorithms and the minimax implementation for the computer moves
* **board.c/h**: handles the game board state memory allocation and visual representation
* **logic.c/h**: manages the win conditions gravity logic for falling tokens and move validation
* **game_manager.c**: coordinates the turns between players and the state machine of the application
* **ui.c/h**: handles all terminal output and user input processing

## Data Structures and Structs
the game relies on several custom structures to manage the complexity of the board and ai evaluations 

### Board Struct
this is the core structure that holds the game state 
* **matrix**: a two dimensional array representing the slots on the board 
* **rows and cols**: integers defining the dimensions of the current game session 
* **last_move**: stores the coordinates of the most recent play to optimize win checking 

### AI State Struct
used during the minimax recursion to evaluate potential moves 
* **score**: an integer representing how favorable a specific board state is 
* **best_column**: the optimal move calculated by the algorithm for a given depth 

## Technical Features
* **minimax algorithm**: the ai calculates several moves ahead using a recursive search to find the best possible outcome 
* **dynamic memory**: the board is allocated dynamically allowing for flexible game sizes if needed 
* **modular design**: easy to extend or replace the ui with a graphical interface in the future 

## How to Run
to compile and run the game on your local machine follow these steps 

1. clone the repository
   git clone https://github.com/MordasovMark/Connect4-C.git
2. compile all source files using gcc
   gcc *.c -o connect4
3. run the executable
   ./connect4
