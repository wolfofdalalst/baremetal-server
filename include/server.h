#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>

struct server {
    int domain;
    int service;
    int protocol;
    unsigned long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(struct server *srv);
};

// Creates and initializes server with socket binding and listening
struct server serverCreate(int domain, int service, int protocol,
                           unsigned long interface, int port, int backlog,
                           void (*launch)(struct server *srv));

#endif  // SERVER_H