/*
 * Tic-Tac-Toe Game Header File
 * Contains function declarations for the game
 */

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function declarations
void initializeBoard(char **board, int size);
void displayBoard(char **board, int size);
int BoardSize();
int MoveValidity(char **board, int size, int row, int col);
void makeMove(char **board, int size, int row, int col, char player);
int conditionWin(char **board, int size, char player);
int conditionDraw(char **board, int size);
void logMove(FILE *logFile, int moveNumber, int player, int row, int col, char **board, int size);
void playGame(char **board, int size, int gameMode);
void instruct();
int selectGameMode();
void generateComputerMove(char **board, int size, int *row, int *col);

#endif