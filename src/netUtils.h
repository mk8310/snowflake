//
// Created by MingKing on 2019-06-02.
//

#ifndef SNOWFLAKE_RPC_NETUTILS_H
#define SNOWFLAKE_RPC_NETUTILS_H

void serve(int port = 9999, int listenNum = 10);

typedef struct sockaddr SA;

void accept_cb(int fd, short events, void *arg);

void socket_read_cb(int fd, short events, void *arg);

int tcp_server_init(int port, int listen_num);

#endif //SNOWFLAKE_RPC_NETUTILS_H
