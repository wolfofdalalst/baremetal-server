#include "server.h"

#include <stdio.h>
#include <stdlib.h>

struct server serverCreate(int domain, int service, int protocol,
                           unsigned long interface, int port, int backlog,
                           void (*launch)(struct server *srv)) {
    struct server srv;

    srv.domain = domain;
    srv.service = service;
    srv.protocol = protocol;
    srv.interface = interface;
    srv.port = port;
    srv.backlog = backlog;

    srv.address.sin_family = domain;
    srv.address.sin_port = htons(port);
    srv.address.sin_addr.s_addr = htonl(interface);

    srv.socket = socket(domain, service, protocol);
    if (srv.socket == 0) {
        perror("Failed to connect to socket...\n");
        exit(EXIT_FAILURE);
    }

    if ((bind(srv.socket, (struct sockaddr *)&srv.address,
              sizeof(srv.address))) < 0) {
        perror("Failed to bind socket...\n");
        exit(EXIT_FAILURE);
    }

    if (listen(srv.socket, backlog) < 0) {
        perror("Failed to listen on socket...\n");
        exit(EXIT_FAILURE);
    }

    srv.launch = launch;

    return srv;
}