#include "httprequest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datastructures/map.h"
#include "datastructures/queue.h"

static int stringCompare(void *a, void *b) { return strcmp((char *)a, (char *)b); }

// Converts method string to enum
enum HTTPMethod methodSelect(const char *method) {
    if (strcmp(method, "GET") == 0) return GET;
    if (strcmp(method, "POST") == 0) return POST;
    if (strcmp(method, "PUT") == 0) return PUT;
    if (strcmp(method, "DELETE") == 0) return DELETE;
    if (strcmp(method, "PATCH") == 0) return PATCH;
    if (strcmp(method, "HEAD") == 0) return HEAD;
    if (strcmp(method, "OPTIONS") == 0) return OPTIONS;
    if (strcmp(method, "TRACE") == 0) return TRACE;
    return UNKNOWN;
}

char *trim_space(char *str) {
    while (*str == ' ') str++;
    return str;
}

struct map *parse_body(char *body, struct map *headers) {
    void *type = headers->search(headers, "Content-Type");
    if (!type) return NULL;

    char *content_type = (char *)type;
    struct map *body_map = createMap(stringCompare);

    if (strcmp(content_type, "application/x-www-form-urlencoded") == 0) {
        struct queue *fields = createQueue();
        char *temp = strdup(body);
        char *pair = strtok(temp, "&");
        while (pair) {
            fields->push(fields, pair, strlen(pair) + 1);
            pair = strtok(NULL, "&");
        }

        while (fields->list->size > 0) {
            char *field = (char *)fields->top(fields);
            char *key = strtok(field, "=");
            char *value = strtok(NULL, "\0");
            if (value) value = trim_space(value);
            body_map->insert(body_map, strdup(key),
                             value ? strdup(value) : strdup(""));
            fields->pop(fields);
        }

        free(temp);
        destroyQueue(fields);
    } else {
        body_map->insert(body_map, strdup("data"), strdup(body));
    }

    return body_map;
}

struct HTTPRequest HTTPRequestCreate(char *requestString) {
    struct HTTPRequest request;

    // Make a local modifiable copy of the request string
    char *requestCopy = malloc(strlen(requestString) + 1);
    strcpy(requestCopy, requestString);

    // Replace the blank line with a delimiter
    for (int i = 0; i < strlen(requestCopy) - 1; i++) {
        if (requestCopy[i] == '\n' && requestCopy[i + 1] == '\n') {
            requestCopy[i + 1] = '|';
        }
    }

    // Split the request into components
    char *requestLine = strtok(requestCopy, "\n");
    char *headerField = strtok(NULL, "|");
    char *body = strtok(NULL, "\0");

    // === Parse Request Line ===
    char *lineCopy = malloc(strlen(requestLine) + 1);
    strcpy(lineCopy, requestLine);

    char *method = strtok(lineCopy, " ");
    request.method = methodSelect(method);

    char *URI = strtok(NULL, " ");
    request.URI = malloc(strlen(URI) + 1);
    strcpy(request.URI, URI);

    char *HTTPVersion = strtok(NULL, "/");
    HTTPVersion = strtok(NULL, "/");
    request.HTTPVersion = (float)atof(HTTPVersion);

    // === Parse Headers ===
    request.headerFields = createMap(stringCompare);
    struct queue *headerQueue = createQueue();

    char *field = strtok(headerField, "\n");
    while (field != NULL) {
        char *fieldCopy = malloc(strlen(field) + 1);
        strcpy(fieldCopy, field);
        headerQueue->push(headerQueue, fieldCopy, strlen(fieldCopy) + 1);
        field = strtok(NULL, "\n");
    }

    char *header = (char *)headerQueue->top(headerQueue);
    while (header != NULL) {
        char *key = strtok(header, ":");
        char *value = strtok(NULL, "\0");
        if (key && value) {
            while (*value == ' ') value++; // Trim leading space
            char *keyCopy = malloc(strlen(key) + 1);
            char *valueCopy = malloc(strlen(value) + 1);
            strcpy(keyCopy, key);
            strcpy(valueCopy, value);
            request.headerFields->insert(request.headerFields, keyCopy, valueCopy);
        }
        headerQueue->pop(headerQueue);
        header = (char *)headerQueue->top(headerQueue);
    }

    // === Parse Body ===
    request.bodyFields = createMap(stringCompare);
    char *contentType = request.headerFields->search(request.headerFields, "Content-Type");
    if (contentType && strcmp(contentType, "application/x-www-form-urlencoded") == 0 && body) {
        char *bodyField = strtok(body, "&");
        while (bodyField) {
            char *pairCopy = malloc(strlen(bodyField) + 1);
            strcpy(pairCopy, bodyField);

            char *key = strtok(pairCopy, "=");
            char *value = strtok(NULL, "\0");
            if (key && value) {
                char *keyCopy = malloc(strlen(key) + 1);
                char *valueCopy = malloc(strlen(value) + 1);
                strcpy(keyCopy, key);
                strcpy(valueCopy, value);
                request.bodyFields->insert(request.bodyFields, keyCopy, valueCopy);
            }

            free(pairCopy);
            bodyField = strtok(NULL, "&");
        }
    } else if (body) {
        char *bodyCopy = malloc(strlen(body) + 1);
        strcpy(bodyCopy, body);
        char *key = malloc(5);
        strcpy(key, "data");
        request.bodyFields->insert(request.bodyFields, key, bodyCopy);
    }

    // Clean up
    free(lineCopy);
    free(requestCopy);
    destroyQueue(headerQueue);

    return request;
}


void HTTPRequestDestroy(struct HTTPRequest *request) {
    if (request->URI) free(request->URI);
    if (request->headerFields) destroyMap(request->headerFields);
    if (request->bodyFields) destroyMap(request->bodyFields);
}
