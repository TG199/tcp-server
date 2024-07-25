#include "socket.h"

/**
 * main - Entry point of client program
 * Return: Always 0 on sucess
 */

int main(void)
{	
	struct addrinfo *server_info;
	struct addrinfo hints;
	int return_val;
	int sockfd;
	char received_msg[1024];
	char *line = NULL;
	size_t line_cap = 0;
	ssize_t line_len;
	int bytes_read;
	int bytes_sent;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	/*get hostname address info*/
	return_val = getaddrinfo(NULL, PORT, &hints, &server_info);
	if (return_val != 0)
	{
		fprintf(stderr, "error: getaddrinfo(), %s\n", gai_strerror(return_val));
		exit(EXIT_FAILURE);
	}

	/*create a socket*/
	sockfd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
	if (sockfd == -1)
	{
		perror("error: socket()");
		exit(EXIT_FAILURE);
	}

	/*connect socket fd to address*/
	return_val = connect(sockfd, server_info->ai_addr, server_info->ai_addrlen);
	if (return_val == -1)
	{
		perror("error: connect()");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(server_info);
	server_info = NULL;

	printf("> ");
	while ((line_len = getline(&line, &line_cap, stdin)) > 0)
	{
		line[line_len] = '\0';

		bytes_sent = send(sockfd, line, line_len, 0);
		if (bytes_sent == -1)
		{
			perror("error:send()");
			exit(EXIT_FAILURE);
		}

		bytes_read = recv(sockfd, received_msg, sizeof received_msg, 0);
		if (bytes_read == -1)
		{
			perror("error: recv()");
			exit(EXIT_FAILURE);
		} else if (bytes_read == 0)
		{
			dprintf(2, "recv(): server closed the connection\n");
			exit(EXIT_FAILURE);
		}
		received_msg[bytes_read] = '\0';
		printf("server says: %s\n", received_msg);
		printf("> ");
	}
	return (0);
}