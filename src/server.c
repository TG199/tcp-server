#include "socket.h"

struct addrinfo *server_info = NULL;
struct addrinfo hints, *p;

int sockfd = -1;
struct Vector *polls_fds = NULL;
struct Connection *conn;
struct pollfd socket_pfd ;
struct pollfd pfd;
size_t num_connections, i, num_poll_fds;

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


    connections = vector_init(sizeof(struct Connection), 0);

    polls_fds = vector_init(sizeof(struct pollfd, 0));


    while (1)
    {
        vector_clear(poll_fds);

        socket_pfd = {socket_fd, POLLIN, 0};
        vector_push(poll_fds, &socket_pfd);

        num_connections = vector_length(connections);

        for (i = 0; i < num_connections;)
        {
            conn = vector_get(connections, i);
            if (conn->state == CONN_STATE_END) 
            {
                close(conn->fd);

                if (i != num_connections - 1)
                {
                    vector_set(connections, i,
                                vector_get(connections, num_connections - 1));
                }

                vector_pop(connections);

                --num_connections;

                continue;
            }
            pfd = {
                .fd = conn->fd,
                .events = (conn->state == CONN_STATE_REQ) ? POLLIN : POLLOUT,
                .revents = 0;
            };
            pfd.events = pfd.events | POLLERR;
            vector_push(poll_fds, &pfd);

            ++i;
        }
        return_val = poll(vector_data(poll_fds), vector_length(poll_fds), -1);
        if (return_val == -1)
        {
            perror("error: poll()");
            return (EXIT_FAILURE);
        }

        num_poll_fds = vector_length(poll_fds);
        for (i = 1; i < num_poll_fds; ++i)
        {
            struct pollfd *pfd = vector_get(poll_fds, i);
            if (pfd->revents)
            {
                struct Connection *conn = vector_get(connections, i - 1);

                if (!conn)
                {
                    continue
                }

                handle_connection_io(conn);
            }
        }

        if (((struct pollfd *)vector_get(poll_fds, 0))->revents & POLLIN)
        {
            accept_new_connection();
        }
    }
    return (0);
}