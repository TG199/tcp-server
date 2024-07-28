#include "socket.h"

/**
 * accept_new_conn - accept new connection to the server
 * Return: true on client connection */
bool accept_new_conn(int sockfd, struct Vector *connections)
{
        struct sockaddr_storage client_addr = {};
        socklen_t addr_size = sizeof client_addr;
        int conn_fd;
        struct Connection conn;

        conn_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);
        if (conn_fd == -1)
        {
                perror("error: accept()");
                return (false);
        }
        conn.fd = conn_fd;
	conn.state = CONN_STATE_REQ;

        vector_push(connections, &conn);

        printf("client %d connected\n", conn_fd);

        return (true);
}

/**
 * handle_conn- handle incoming connections
 * Returns: Noting
 */

void handle_conn(struct Connection *conn)
{
        int bytes_read;
        int bytes_sent, bytes_sent2;

        if (conn->state == CONN_STATE_REQ)
        {
                bytes_read = recv(conn->fd, conn->read_buf, sizeof(conn->read_buf) - 1, 0);
                if (bytes_read == -1)
                {
                        perror("error: recv()");;
                        conn->state = CONN_STATE_END;
                        return;
                } else if (bytes_read == 0)
                {
                        printf("client %d disconnected\n", conn->fd);
                        conn->state = CONN_STATE_END;
                        return;
                }
                conn->read_buf[bytes_read] = '\0';

                conn->state = CONN_STATE_RES;
                
                printf("client %d says: %s\n", conn->fd, conn->read_buf);
        
        } else if (conn->state == CONN_STATE_RES)
        {
                char reply_start[] = "you said: ";
                memcpy(conn->write_buf, reply_start, sizeof(reply_start));

                strncat(conn->write_buf, conn->read_buf,
                        sizeof(conn->write_buf) - sizeof(reply_start));

                bytes_sent2 = send(conn->fd, conn->write_buf, strlen(conn->write_buf), 0);
                if (bytes_sent2 == -1)
                {
                        perror("handle_client_message(): send");
                        return;
                }

                conn->state = CONN_STATE_REQ;
        } else {
                dprintf(2, "handle_conn():invalid state\n");
                exit(EXIT_FAILURE);
        }

}
