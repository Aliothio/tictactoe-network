#include "clientfuncs.h"


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