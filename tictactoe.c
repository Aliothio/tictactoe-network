#include "tictactoe.h"

/**
 * @brief Initializes all elements in the 2d array with '*' called at start of game
 * 
 * @param board The 2d array to be initialized
 */
void initializeBoard(char *board)
{
    for(int i = 0; i < NUM_ROWS; i++)
    {
        for(int j = 0; j < NUM_COLS; j++)
        {
            board[i*NUM_COLS+j] = '*';
        }
    }
    return;
}

/**
 * @brief Display the board on screen
 * 
 * @param board The board to be displayed
 */
void displayBoard(const char *board)
{
    printf("   1  2  3\n");
    for(int i = 0; i < NUM_ROWS; i++)
    {
        printf("%d  ", i+1);
        for(int j = 0; j < NUM_COLS; j++)
        {
            printf("%c  ", *board++);
        }
        printf("\n");
    }
    return;
}

/**
 * @brief Update the board's row and column element with the playerToken
 * 
 * @param board The board to be updated
 * @param row Which row to update
 * @param col Which column to update
 * @param playerToken The Token to be used
 */
void updateBoard(char *board, int row, int col, char playerToken)
{
    // Sets the row and col in the board to playerToken, isValidMove will be checked before this is called
    board[(row-1) * NUM_COLS + (col-1)] = playerToken;
}

/**
 * @brief Checks if a given move is valid
 * 
 * @param board Board to check
 * @param row Row to check
 * @param col Column to check
 * @return int Return 1 if valid, 0 if not
 */
int isValidMove(const char *board, int row, int col)
{
    // Move is valid if it is on the board and there is a * there
    if ((row <= NUM_ROWS && row > 0) && (col <= NUM_COLS && col > 0) && (board[((row-1) * NUM_COLS) + (col-1)] == '*'))
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Checks if the current player has won
 * 
 * @param board Board to see if there is a win
 * @param playerToken Token to check for
 * @return int Return 1 if a win, otherwise return 0
 */
int isWin(const char *board, char playerToken)
{
    // There is a win if there are three X characters or O characters in a row, column, or diagonal
    int win = 0;
    // Checking for a win in all rows and columns
    for (int i = 0; i < NUM_ROWS; i++)
    {
        if ((board[(i * NUM_ROWS) + 0] == playerToken && board[(i * NUM_ROWS) + 1] == playerToken && board[(i * NUM_ROWS) + 2] == playerToken) || (board[(0 * NUM_ROWS) + i] == playerToken && board[(1 * NUM_ROWS) + i] == playerToken && board[(2 * NUM_ROWS) + i] == playerToken))
        {
            win = 1;
            return win;
        }

    }
    // Checking for a win in the diagonals
    if ((board[(0 * NUM_ROWS) + 0] == playerToken && board[(1 * NUM_ROWS) + 1] == playerToken && board[(2 * NUM_ROWS) + 2] == playerToken) || (board[(0 * NUM_ROWS) + 2] == playerToken && board[(1 * NUM_ROWS) + 1] == playerToken && board[(2 * NUM_ROWS) + 0] == playerToken))
    {
        win = 1;
        return win;
    }

    return win;
}

/**
 * @brief Checks if the board is full
 * 
 * @param board Board to check
 * @return int Return 1 if the board is full, otherwise return 0
 */
int isFull(const char *board)
{
    // Assume board is full
    int full = 1;
    
    // Sets not full if there is a * anywhere
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLS; j++)
        {
            if (board[i * NUM_COLS + j] == '*')
            {
                full = 0;
                return full;
            }
        }
    }

    printf("There has been a tie\n");
    return full;
}