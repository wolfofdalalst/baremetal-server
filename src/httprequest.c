#include "httprequest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum HTTPMethod methodSelect(const char *method) {
    if (strcmp(method, "GET") == 0) {
        return GET;
    } else if (strcmp(method, "POST") == 0) {
        return POST;
    } else if (strcmp(method, "PUT") == 0) {
        return PUT;
    } else if (strcmp(method, "DELETE") == 0) {
        return DELETE;
    } else if (strcmp(method, "PATCH") == 0) {
        return PATCH;
    } else if (strcmp(method, "HEAD") == 0) {
        return HEAD;
    } else if (strcmp(method, "OPTIONS") == 0) {
        return OPTIONS;
    } else if (strcmp(method, "TRACE") == 0) {
        return TRACE;
    }
}

struct HTTPRequest HTTPRequestCreate(char *requestString) {
    struct HTTPRequest request;
    char requested[strlen(requestString)];
    strcpy(requested, requestString);
    for (int i = 0; i < strlen(requested) - 1; i++) {
        if (requested[i] == '\n' && requested[i + 1] == '\n') {
            printf("a/n");
            requested[i + 1] = '|';
        }
    }
    char *requestLine = strtok(requestString, "\n");
    char *headerField = strtok(NULL, "|");
    char *body = strtok(NULL, "\0");
    char *method = strtok(requestLine, " ");
    request.method = methodSelect(method);
    char *URI = strtok(NULL, " ");
    request.URI = URI;
    char *HTTPVersion = strtok(NULL, " ");
    HTTPVersion = strtok(NULL, "/");
    HTTPVersion = strtok(NULL, "/");
    request.HTTPVersion = (float)atof(HTTPVersion);

    return request;
}