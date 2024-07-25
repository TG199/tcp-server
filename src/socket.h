#ifndef SOCKET_H
#define SOCKET_H

#include <netdb.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>


/*Port to run server*/
const char *PORT = "4001";
#define BACKLOG 5;

struct addrinfo *server_info = NULL;
struct addrinfo hints, *p;

int sockfd = -1;

struct Vector *polls_fds = NULL;

int main(void)
{
    int return_val;
    int yes;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    return_val = getaddrinfo(NULL, PORT, &hints, &server_info);

    if (return_val != 0)
    {
        fprintf(stderr, "error: getaddrinfo() %s\n", gai_strerro(return_val));
        exit(EXIT_FAILURE);
    }

    for (p = server_info; p != NULL; p p->ai_next)
    {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1)
        {
            perror("error: socket");
            continue;
        }
        yes = 1;
        return_val = (setsockopt(sockfd, SOL_SOCKET, &yes, sizeof yes));
        if (return_val == -1)
        {
            perror("error: setsockopt()");
            exit(EXIT_FAILURE);
        }

        return_val = bind(sockfd,p->ai_addr, p->ai_addrlen);
        if (return_val == -1)
        {
            perror("error: bind");
            continue;
        }
        break;
    }

    if (!p)
    {
        fprintf(stderr, "failed to bind\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(server_info);
    server_info = NULL;

    return_val = listen(sockfd, BACKLOG);
    if (return_val == -1)
    {
        perror("error: listen()");
        exit(EXIT_FAILURE);
    }
    printf("server listening on port %s...\n", PORT);
}













#endif
