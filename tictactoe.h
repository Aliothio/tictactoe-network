#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>

#define NUM_ROWS 3
#define NUM_COLS 3
#define NUM_PLAYERS 2



void initializeBoard(char *board);
void displayBoard(const char *board);
void updateBoard(char *board, int row, int col, char playerToken);
int isValidMove(const char *board, int row, int col);
int isWin(const char *board, char playerToken);
int isFull(const char *board);


#endif