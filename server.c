/**
 * @file server.c
 * @author Logan Rostron (loganplaysrunescape@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include "tictactoe.h"
#include "serverfuncs.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printNameAndIP();

    

    
    

    // Setup Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Creating Socket");
        exit(EXIT_FAILURE);
    }

    // Setup server info
    struct sockaddr_in serv_addr;
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Binding");
        exit(EXIT_FAILURE);
    }

    // Start listening
    if (listen(sockfd, 3) < 0)
    {
        close(sockfd);
        perror("Listening");
        exit(EXIT_FAILURE);
    }

    // Waiting and Accepting
    while(1)
    {
        // Variables used for the game loop
        const char PLAYER_TOKEN[NUM_PLAYERS] = {'X', 'O'};
        char mainBoard[NUM_ROWS * NUM_COLS];
        int currentPlayer = 0;
        int inputRow = 0;
        int inputCol = 0;

        // Setup Board And Display The Empty Board
        initializeBoard(mainBoard);

        printf("Waiting for the new player to connect...\n");


        int newsockfd = accept(sockfd, NULL, NULL);
        if (newsockfd == -1)
        {
            perror("Accepting");
            exit(EXIT_FAILURE);
        }

        printf("The player is connected...\n");

        displayBoard(mainBoard);
        char buffer[256];
        memset(buffer, 0, 255);
        sprintf(buffer, "%s", mainBoard);

        if (write(newsockfd, buffer, 255) < 0)
        {
            perror("Writing to socket");
            close(newsockfd);
            exit(EXIT_FAILURE);
        }


        // Game Loop
        while(!isFull(mainBoard))
        {
            if (currentPlayer == 0) // Player Turn
            {
                // Get player input
                printf("Player turn...\n");
                memset(buffer, 0, 255);
                buffer[0] = 1;
                if (write(newsockfd, buffer, 255) < 0)
                {
                    perror("Writing to socket");
                    close(newsockfd);
                    exit(EXIT_FAILURE);
                }
                
                memset(buffer, 0, 255);
                if (read(newsockfd, buffer, 255) < 0)
                {
                    perror("Reading from socket");
                    close(newsockfd);
                    exit(EXIT_FAILURE);
                }
                sscanf(buffer, "%d %d", &inputRow, &inputCol);

                // Checks if the inputed location is valid and loops until it is valid
                while(!isValidMove(mainBoard, inputRow, inputCol))
                {
                    printf("%d %d\n", inputRow, inputCol);
                    memset(buffer, 0, 255);
                    buffer[0] = 2;
                    if (write(newsockfd, buffer, 255) < 0)
                    {
                        perror("Writing to socket");
                        close(newsockfd);
                        exit(EXIT_FAILURE);
                    }

                    memset(buffer, 0, 255);
                    if (read(newsockfd, buffer, 255) < 0)
                    {
                        perror("Reading from socket");
                        close(newsockfd);
                        exit(EXIT_FAILURE);
                    }
                    sscanf(buffer, "%d %d", &inputRow, &inputCol);
                }

                printf("Player enter: %d %d\n", inputRow, inputCol);
            }
            else // Computer Turn
            {

                printf("Computer Turn...\n");

                // Generate a location for the computer to place their token
                while(!isValidMove(mainBoard, inputRow, inputCol))
                {
                    // Using srand and time to get a new seed for rand
                    srand(time(0));
                    inputRow = rand() % (3) + 1;
                    srand(time(0));
                    inputCol = rand() % (3) + 1;   
                }
                printf("Computer enter a row, column: %d %d\n", inputRow, inputCol);
                memset(buffer, 0, 255);
                sprintf(buffer, "3 %d %d", inputRow, inputCol);
                if (write(newsockfd, buffer, 255) < 0)
                {
                    perror("Writing to socket");
                    close(newsockfd);
                    exit(EXIT_FAILURE);
                }
            }

            updateBoard(mainBoard, inputRow, inputCol, PLAYER_TOKEN[currentPlayer]);

            displayBoard(mainBoard);

            // Send board
            memset(buffer, 0, 255);
            sprintf(buffer, "%s", mainBoard);
            if (write(newsockfd, buffer, 255) < 0)
            {
                perror("Writing to socket");
                close(newsockfd);
                exit(EXIT_FAILURE);
            }

            /*if (read(newsockfd, buffer, 1) < 0)
            {
                perror("Reading from socket");
                exit(EXIT_FAILURE);
            }*/

            // Checks if there has been a winner and says the token of the winner
            if (isWin(mainBoard, PLAYER_TOKEN[currentPlayer]))
            {
                if(currentPlayer == 0)
                {
                    printf("Player won!!!\n");
                } else 
                {
                    printf("Computer won!!!\n");
                }

                memset(buffer, 0, 255);
                sprintf(buffer, "4 %d", currentPlayer+1);
                if (write(newsockfd, buffer, 255) < 0)
                {
                    perror("Writing to socket");
                    close(newsockfd);
                    exit(EXIT_FAILURE);
                }
                break;
            }

            // Switches between player 1 and 2
            currentPlayer = !currentPlayer;
        }
        
        if (isFull(mainBoard))
        {
            memset(buffer, 0, 255);
            sprintf(buffer, "5");
            if (write(newsockfd, buffer, 255) < 0)
            {
                perror("Writing to socket");
                close(newsockfd);
                exit(EXIT_FAILURE);
            }
            printf("Tie Game...\n");
        }

        close(newsockfd);
    }

    return 0;
}