#include "socket.h"


/**
 * main - Entry point of client program
 * Return: Always 0 on sucess
 */

int main(void)
{
	int return_val;
	int sockfd;

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;


	/*get hostname address info*/
	return_val = getaddrinfo(NULL, PORT, &hints, &server_info);
	if (return_val != 0)
	{
		fprintf(stderr, "error: getaddrinfo(), %s\n", gai_sterror(return_val));
		exit(EXIT_FAILURE)
	}

	/*create a socket*/
	sockfd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
	if (sockfd == -1)
	{
		perror("error: socket()");
		exit(EXIT_FAILURE);
	}

	/*create a connection*/
	return_val = connect(sockfd, server_info->ai_addr, server_info->ai_addrlen);
	if (return_val == -1)
	{
		perror("error: connect()");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(server_info);
	server_info = NULL;
}