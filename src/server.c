#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Creates and initializes server with socket binding and listening
struct server serverCreate(int domain, int service, int protocol,
                           unsigned long interface, int port, int backlog,
                           void (*launch)(struct server *srv)) {
    struct server srv;
    memset(&srv, 0, sizeof(srv));

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
    if (srv.socket < 0) {
        perror("Socket creation failed");
        srv.socket = -1;
        return srv;
    }

    if (bind(srv.socket, (struct sockaddr *)&srv.address, sizeof(srv.address)) < 0) {
        perror("Bind failed");
        close(srv.socket);
        srv.socket = -1;
        return srv;
    }

    if (listen(srv.socket, backlog) < 0) {
        perror("Listen failed");
        close(srv.socket);
        srv.socket = -1;
        return srv;
    }

    srv.launch = launch;
    return srv;
}
