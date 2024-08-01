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
#include <assert.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


/*Port to run server*/
#define PORT "4001"

#define BACKLOG 5


/*Connection struct */
enum ConnectionState {
    CONN_STATE_REQ = 0,
    CONN_STATE_RES,
    CONN_STATE_END,
};

struct Connection {
    int fd;
    enum ConnectionState state;
    char read_buf[1024];
    char write_buf[1024];
};


/*Vector struct*/
#define VECTOR_CAP 10

struct Vector {
    void *data;
    size_t length;
    size_t capacity;
    size_t elem_size;
};
void safe_free(void **ptr);

struct Vector *vector_init(size_t elem_size, size_t capacity);
void vector_free(struct Vector *vector);
bool vector_push(struct Vector *vector, void *element);
void *vector_pop(struct Vector *vector);
void *vector_get(struct Vector *vector, size_t idx);
void vector_set(struct Vector *vector, size_t idx, void *element);
void vector_clear(struct Vector *vector);
void *vector_data(struct Vector *vector);
size_t vector_length(struct Vector *vector);
size_t vector_capacity(struct Vector *vector);
size_t vector_elem_size(struct Vector *vector);

bool accept_new_conn(int sockfd, struct Vector *connections);
void handle_conn(struct Connection *conn);


/*Openssl functions */
void init_openssl(void);
void cleanup_openssl(void);
SSL_CTX *create_context(void);
void configure_context(SSL_CTX *ctx);

#endif
