#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "server.h"
#include "httprequest.h"
#include "fileutils.h"

#define BUFFER_SIZE 30000
#define WWW_ROOT "./www"

// Sends HTTP response to client socket
void sendResponse(int socket, int status_code, const char *status_text, 
                  const char *content_type, const char *content, size_t content_length) {
    char header[1024];
    int header_len = snprintf(header, sizeof(header),
        "HTTP/1.1 %d %s\r\n"
        "Server: Baremetal-C-Server/1.0\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n",
        status_code, status_text, content_type, content_length);
    
    write(socket, header, header_len);
    if (content && content_length > 0) {
        write(socket, content, content_length);
    }
}

// Handles incoming HTTP requests and serves files
void handleRequest(int socket, const char *request_string) {
    struct HTTPRequest request = HTTPRequestCreate((char*)request_string);
    
    if (request.method != GET) {
        const char *error_msg = "<html><body><h1>405 Method Not Allowed</h1></body></html>";
        sendResponse(socket, 405, "Method Not Allowed", "text/html", error_msg, strlen(error_msg));
        HTTPRequestDestroy(&request);
        return;
    }
    
    char filepath[512];
    if (strcmp(request.URI, "/") == 0) {
        snprintf(filepath, sizeof(filepath), "%s/index.html", WWW_ROOT);
    } else {
        const char *uri = request.URI + 1;
        snprintf(filepath, sizeof(filepath), "%s/%s", WWW_ROOT, uri);
    }
    
    printf("Requested file: %s\n", filepath);
    
    struct FileContent *file = readFile(filepath);
    if (file) {
        sendResponse(socket, 200, "OK", file->mime_type, file->content, file->size);
        freeFileContent(file);
    } else {
        char notfound_path[512];
        snprintf(notfound_path, sizeof(notfound_path), "%s/404.html", WWW_ROOT);
        
        struct FileContent *notfound = readFile(notfound_path);
        if (notfound) {
            sendResponse(socket, 404, "Not Found", notfound->mime_type, notfound->content, notfound->size);
            freeFileContent(notfound);
        } else {
            const char *error_msg = "<html><body><h1>404 Not Found</h1></body></html>";
            sendResponse(socket, 404, "Not Found", "text/html", error_msg, strlen(error_msg));
        }
    }
    
    HTTPRequestDestroy(&request);
}

// Launches server and handles client connections
void launch(struct server *srv) {
    char buffer[BUFFER_SIZE];
    
    while (1) {
        printf("Server listening on port %d...\n", srv->port);
        int address_len = sizeof(srv->address);
        int newSocket = accept(srv->socket, (struct sockaddr *)&srv->address,
                               (socklen_t *)&address_len);
        
        if (newSocket < 0) {
            perror("Accept failed");
            continue;
        }
        
        memset(buffer, 0, BUFFER_SIZE);
        
        ssize_t bytes_read = read(newSocket, buffer, BUFFER_SIZE - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            printf("Request received:\n%s\n", buffer);
            handleRequest(newSocket, buffer);
        }
        
        close(newSocket);
    }
}

// Main entry point - creates and launches HTTP server
int main(void) {
    struct server srv =
        serverCreate(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);
    srv.launch(&srv);
    return 0;
}