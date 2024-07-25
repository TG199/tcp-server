#ifndef SOCKET_H
#define SOCKET_H


#include <netdb.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <stddef.h>


/*Port to run server*/
const char *PORT = "4001";
#define BACKLOG 5;

enum ConnectionState {
    CONN_STATE_REQ = 0,
    CONN_STATE_RES,
    CONN_STATS_END,
};

struct Connection {
    int fd;
    enum ConnectionState state;
    char read_buf[1024];
    char write_buf[1024];
};

static bool accept_new_connection(void);
static void handle_connection_io(struct Connection *conn);


#endif
