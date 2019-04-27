#ifndef __SERVAL_H_
#define __SERVAL_H_

#define LOG_INFO(x, ...) do {printf("%s: ", __FUNCTION__); printf(x, ##__VA_ARGS__); printf("\n"); } while(0);
#define LOG_ERROR(x, ...) do {printf("%s:ERROR: ", __FUNCTION__); printf(x, ##__VA_ARGS__); printf("\n"); } while(0);
#define LOG_DEBUG LOG_INFO

#define SERVAL_MAX_PORT (65535)
#define SERVAL_MAX_PORT_LEN (6)
#define SERVAL_SOCKET_BACKLOG (10)

typedef struct {
    bool is_open;
    int client_fd;
} serval_client_t;

typedef void (*serval_connect_t)(serval_client_t *client, void *priv_data);
typedef void (*serval_message_t)(serval_client_t *client, char *data, size_t length, void *priv_data);

typedef enum {
    SERVAL_OPT_PORT,
    SERVAL_OPT_IFACE,
    SERVAL_OPT_CONNECT_FUNC,
    SERVAL_OPT_CONNECT_PRIV,
    SERVAL_OPT_MESSAGE_FUNC,
    SERVAL_OPT_MESSAGE_PRIV,
    SERVAL_OPT_INVALID,
} serval_opt_t;

typedef struct {
    bool _valid;
    bool _running;
    char _port[SERVAL_MAX_PORT_LEN];
    int  server_fd;
    void *connect_priv;
    void *message_priv;
    serval_connect_t connect_func;
    serval_message_t message_func;
} serval_t;

int serval_init(serval_t *serval);
int serval_setopt(serval_t *serval, serval_opt_t opt, void *arg);
int serval_start(serval_t *serval);
int serval_stop(serval_t *serval);

int serval_client_is_open(serval_client_t *client);
int serval_client_get_fd(serval_client_t *client);
int serval_client_close(serval_client_t *client);
int serval_client_send(serval_client_t *client, char *msg, size_t length);

#endif
