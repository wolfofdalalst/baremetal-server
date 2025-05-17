#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>

struct server {
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(struct server *srv);
};

struct server serverCreate(int domain, int service, int protocol,
                           u_long interface, int port, int backlog,
                           void (*launch)(struct server *srv));

#endif  // SERVER_H