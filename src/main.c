#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

#define BUFFER_SIZE 30000

void launch(struct server *srv) {
    char buffer[BUFFER_SIZE];
    char *hello =
        "HTTP/1.1 200 OK\r\n"
        "Date: Mon, 27 Jul 2009 12:28:53 GMT\r\n"
        "Server: Apache/2.2.14 (Win32)\r\n"
        "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\n"
        "Content-Length: 55\r\n"
        "Content-Type: text/html\r\n"
        "Connection: Closed\r\n"
        "\r\n"
        "<html><body><h1>Hasta la vista, baby!</h1></body></html>";

    while (1) {
        printf("Server launched\n");
        int address_len = sizeof(srv->address);
        int newSocket = accept(srv->socket, (struct sockaddr *)&srv->address,
                               (socklen_t *)&address_len);
        read(newSocket, buffer, BUFFER_SIZE);
        printf("%s\n", buffer);
        write(newSocket, hello, strlen(hello));
        close(newSocket);
    }
}

int main(void) {
    struct server srv =
        serverCreate(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);
    srv.launch(&srv);
    return 0;
}