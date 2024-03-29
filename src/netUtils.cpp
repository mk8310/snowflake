//
// Created by MingKing on 2019-06-02.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <getopt.h>
#include <event.h>
#include <sstream>
#include <iostream>

#include "netUtils.h"
#include "SnowFlake.h"


void serve(int port, int listenNum) {
    int listener = tcp_server_init(port, listenNum);
    if (listener == -1) {
        perror("tcp_server_init error");
        return;
    }

    struct event_base *base = event_base_new();

    // 监听客户端请求链接事件
    struct event *ev_listen = event_new(base, listener, EV_READ | EV_PERSIST, accept_cb, base);

    event_add(ev_listen, NULL);

    std::cout << "listen ......" << std::endl;
    event_base_dispatch(base);
}

void accept_cb(int fd, short events, void *arg) {
    evutil_socket_t sockfd;

    struct sockaddr_in client;
    socklen_t len = sizeof(client);

    sockfd = ::accept(fd, (struct sockaddr *) &client, &len);
    evutil_make_socket_nonblocking(sockfd);

    printf("accept a client %d\n", sockfd);

    struct event_base *base = (event_base *) arg;

    //动态创建一个event结构体，并将其作为回调参数传递给
    struct event *ev = event_new(NULL, -1, 0, NULL, NULL);
    event_assign(ev, base, sockfd, EV_READ | EV_PERSIST, socket_read_cb, (void *) ev);

    event_add(ev, NULL);
}


void socket_read_cb(int fd, short events, void *arg) {
    char msg[4096];
    struct event *ev = (struct event *) arg;
    int len = read(fd, msg, sizeof(msg) - 1);

    if (len <= 0) {
        printf("some error happen when read\n");
        event_free(ev);
        close(fd);
        return;
    }

    msg[len] = '\0';
    printf("recv the client msg : %s\n", msg);
    char reply_msg[4096];

    SnowFlake *snowFlake = SnowFlake::getInstance();
    long id = snowFlake->Next();
    std::stringstream stream;
    stream << id;
    stream >> reply_msg;

    write(fd, reply_msg, strlen(reply_msg));

    printf("generate new id:%ld\n", id);
}


int tcp_server_init(int port, int listen_num) {
    int errno_save;
    evutil_socket_t listener;

    listener = ::socket(AF_INET, SOCK_STREAM, 0);
    if (listener == -1)
        return -1;

    //允许多次绑定同一个地址。要用在socket和bind之间
    evutil_make_listen_socket_reuseable(listener);

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(port);

    if (::bind(listener, (SA *) &sin, sizeof(sin)) < 0)
        goto error;

    if (::listen(listener, listen_num) < 0)
        goto error;


    //跨平台统一接口，将套接字设置为非阻塞状态
    evutil_make_socket_nonblocking(listener);

    return listener;

    error:
    errno_save = errno;
    evutil_closesocket(listener);
    errno = errno_save;

    return -1;
}
