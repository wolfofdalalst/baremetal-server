#include <stdio.h>
#include <stdlib.h>

#include "httprequest.h"

const char *methodToString(enum HTTPMethod method) {
    switch (method) {
        case GET:
            return "GET";
        case POST:
            return "POST";
        case PUT:
            return "PUT";
        case DELETE:
            return "DELETE";
        case PATCH:
            return "PATCH";
        case HEAD:
            return "HEAD";
        case OPTIONS:
            return "OPTIONS";
        case TRACE:
            return "TRACE";
        default:
            return "UNKNOWN";
    }
}

void traverse(struct listNode *n) {
    if (!n) return;
    traverse(n->prev);
    printf("  %s: %s\n", (char *)n->key, (char *)n->data);
    traverse(n->next);
}

void printMap(struct map *m) {
    if (!m) return;
    struct binarySearchTree *tree = m->tree;
    struct listNode *node = tree->root;

    traverse(node);
}

int main() {
    char requestString[] =
        "POST /submit-form HTTP/1.1\n"
        "Host: example.com\n"
        "Content-Type: application/x-www-form-urlencoded\n"
        "Content-Length: 32\n"
        "Connection: keep-alive\n"
        "\n"
        "username=admin&password=secret";

    struct HTTPRequest request = HTTPRequestCreate(requestString);

    printf("Method: %s\n", methodToString(request.method));
    printf("URI: %s\n", request.URI);
    printf("HTTP Version: %.1f\n\n", request.HTTPVersion);

    printf("Headers:\n");
    printMap(request.headerFields);

    printf("\nBody:\n");
    printMap(request.bodyFields);

    HTTPRequestDestroy(&request);

    return 0;
}
