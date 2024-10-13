#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BACKLOG 1

int main(int argc, char *argv[])
{
    int sockfd;
    int stop_running;
    int port;
    struct sockaddr_in serv_addr;

    stop_running = 0;

    /* Check if user provided port number */
    if (argc < 2)
    {
        printf("Usage: ./server <port>\n");
        stop_running = 1;
    }
    /* Get port number */
    else
    {
        port = atoi(argv[1]);
        if (port <= 0)
        {
            printf("Invalid port number: %d\n", port);
            stop_running = 1;
        }
    }


    /* Create socket(IPv4, TCP) */ 
    if (!stop_running)
    {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
            printf("Error creating socket\n");
            stop_running = 1;
        }
    }
    
    
    if (!stop_running)
    {
        /* Zero out serv_addr struct and configure */
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET; /* IPv4 */ 
        serv_addr.sin_addr.s_addr = INADDR_ANY; /* Bind to all interfaces */
        serv_addr.sin_port = htons(port); /* Port */ 

        /* Bind socket to the address and port */
        if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("Error binding socket\n");
            stop_running = 1;
        }
    }

    /* Listen for connections */ 
    if (!stop_running)
    {
        if (listen(sockfd, BACKLOG) < 0)
        {
            printf("Error listening on socket\n");
            stop_running = 1;
        }
        else
        {
            printf("Server is listening on port %d\n", port);
        }
    }

    /* Loop to accept and handle clients */
    while (!stop_running) 
    {

    }
    
    return 0;
}