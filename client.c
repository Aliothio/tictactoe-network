/**
 * @file client.c
 * @author Logan Rostron (loganplaysrunescape@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-27
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
#include "clientfuncs.h"


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int inputRow = 0;
    int inputCol = 0;

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
    serv_addr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
    {
        perror("Invalid address / Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connecting");
        exit(EXIT_FAILURE);
    }

    printf("Welcome to the TicTacToe game\n");

    char buffer[256];
    memset(buffer, 0, 255);

    if (read(sockfd, buffer, 255) < 0)
    {
        perror("Reading from socket");
        exit(EXIT_FAILURE);
    }


    displayBoard(buffer);
    memset(buffer, 0, 255);

    // Game Loop
    while(1)
    {
        if (buffer[0] == 0)
        {
            memset(buffer, 0, 255);
            if (read(sockfd, buffer, 255) < 0)
            {
                perror("Reading from socket");
                exit(EXIT_FAILURE);
            }
        }

        if (buffer[0] == 1)
        {
            printf("Player Turn...\n");
            printf("Enter a row, column: ");
            scanf("%d%d", &inputRow, &inputCol);

            memset(buffer, 0, 255);
            sprintf(buffer, "%d %d", inputRow, inputCol);
            if (write(sockfd, buffer, 255) < 0)
            {
                perror("Reading from socket");
                exit(EXIT_FAILURE);
            }
        }

        memset(buffer, 0, 255);
        if (read(sockfd, buffer, 255) < 0)
        {
            perror("Reading from socket");
            exit(EXIT_FAILURE);
        }

        while (buffer[0] == 2)
        {
            printf("Enter a row and column that is on the board and is in an empty spot: ");
            scanf("%d%d", &inputRow, &inputCol);

            memset(buffer, 0, 255);
            sprintf(buffer, "%d %d", inputRow, inputCol);
            if (write(sockfd, buffer, 255) < 0)
            {
                perror("Reading from socket");
                exit(EXIT_FAILURE);
            }

            memset(buffer, 0, 255);
            if (read(sockfd, buffer, 255) < 0)
            {
                perror("Reading from socket");
                exit(EXIT_FAILURE);
            }
        }

        displayBoard(buffer);

        /*if (write(sockfd, "1", 1) < 0)
        {
            perror("Writing to socket");
            close(sockfd);
            exit(EXIT_FAILURE);
        }*/

        // Computer Turn or Winner or Tie
        memset(buffer, 0, 255);
        if (read(sockfd, buffer, 255) < 0)
        {
            perror("Reading from socket");
            exit(EXIT_FAILURE);
        }

        if (buffer[0] == '3') // Computer Turn
        {
            printf("Computer Turn...\nComputer enter a row, column: %d %d\n", atoi(&buffer[2]), atoi(&buffer[4]));

            memset(buffer, 0, 255);
            if (read(sockfd, buffer, 255) < 0)
            {
                perror("Reading from socket");
                exit(EXIT_FAILURE);
            }

            displayBoard(buffer);

            memset(buffer, 0, 255);
            if (read(sockfd, buffer, 255) < 0)
            {
                perror("Reading from socket");
                exit(EXIT_FAILURE);
            }
        } 
        if (buffer[0] == '4') // Winning condition met
        {
            if (atoi(&buffer[2]) == 1)
            {
                printf("Player won!!!\n");
            } else
            {
                printf("Computer won!!!\n");
            }
            break;
        } else if (buffer[0] == '5') // Tie Game
        {
            printf("Tie Game...\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}