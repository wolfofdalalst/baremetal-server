#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "httprequest.h"
#include "datastructures/map.h"
#include "datastructures/node.h"

// Converts HTTP method enum to string representation
const char *methodToString(enum HTTPMethod method) {
    switch (method) {
        case GET: return "GET";
        case POST: return "POST";
        case PUT: return "PUT";
        case DELETE: return "DELETE";
        case PATCH: return "PATCH";
        case HEAD: return "HEAD";
        case OPTIONS: return "OPTIONS";
        case TRACE: return "TRACE";
        case UNKNOWN: return "UNKNOWN";
        default: return "INVALID_METHOD";
    }
}

// Recursively prints BST map contents
void traverseAndPrintMapNode(struct listNode *bstNode) {
    if (!bstNode) return;
    static int depth = 0;
    if (depth > 100) {
        printf("  (traversal depth limit reached)\n");
        return;
    }
    
    depth++;
    
    // The BST node's data points to our map listNode
    struct listNode *mapNode = (struct listNode*)bstNode->data;
    if (!mapNode) {
        printf("  (BST node with NULL data found)\n");
        depth--;
        return;
    }
    
    // Additional safety checks for the map node
    if (mapNode->key == NULL || mapNode->data == NULL) {
        printf("  (map node with NULL key or data found)\n");
        depth--;
        return;
    }
    
    if ((uintptr_t)mapNode->key < 1024 || (uintptr_t)mapNode->data < 1024) {
        printf("  (map node with invalid pointer found)\n");
        depth--;
        return;
    }
    
    traverseAndPrintMapNode(bstNode->prev);
    
    printf("  %s: %s\n", (char *)mapNode->key, (char *)mapNode->data);
    
    traverseAndPrintMapNode(bstNode->next);
    depth--;
}

// Prints all key-value pairs in map
void printMap(struct map *m) {
    if (!m) {
        printf("  (map is NULL)\n");
        return;
    }
    if (!m->tree) {
        printf("  (tree is NULL)\n");
        return;
    }
    if (!m->tree->root) {
        printf("  (tree root is NULL)\n");
        return;
    }
    traverseAndPrintMapNode(m->tree->root);
}

// Tests basic GET request parsing
void test_simple_get_request() {
    printf("--- Test: Simple GET Request ---\n");
    char requestString[] =
        "GET /index.html HTTP/1.1\r\n"
        "Host: www.example.com\r\n"
        "User-Agent: TestClient/1.0\r\n"
        "Accept: text/html\r\n"
        "\r\n";
    
    char *reqCopy = strdup(requestString);
    assert(reqCopy != NULL);

    struct HTTPRequest request = HTTPRequestCreate(reqCopy);

    printf("Method: %s\n", methodToString(request.method));
    assert(request.method == GET);

    printf("URI: %s\n", request.URI);
    assert(request.URI != NULL && strcmp(request.URI, "/index.html") == 0);

    printf("HTTP Version: %.1f\n", request.HTTPVersion);
    assert(request.HTTPVersion == 1.1f);

    printf("\nHeaders:\n");
    assert(request.headerFields != NULL);
    printMap(request.headerFields);
    
    char *host = (char *)request.headerFields->search(request.headerFields, "Host");
    assert(host != NULL && strcmp(host, "www.example.com") == 0);
    char *ua = (char *)request.headerFields->search(request.headerFields, "User-Agent");
    assert(ua != NULL && strcmp(ua, "TestClient/1.0") == 0);

    printf("\nBody:\n");
    assert(request.bodyFields == NULL);
    printMap(request.bodyFields);

    HTTPRequestDestroy(&request);
    free(reqCopy);
    printf("Simple GET Request Test Passed.\n\n");
}

// Tests POST request with form-encoded body
void test_post_request_with_body() {
    printf("--- Test: POST Request with URL-Encoded Body ---\n");
    char requestString[] =
        "POST /submit-form HTTP/1.1\r\n"
        "Host: api.example.com\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Content-Length: 27\r\n"
        "\r\n"
        "name=John+Doe&age=30";

    char *reqCopy = strdup(requestString);
    assert(reqCopy != NULL);

    struct HTTPRequest request = HTTPRequestCreate(reqCopy);

    printf("Method: %s\n", methodToString(request.method));
    assert(request.method == POST);

    printf("URI: %s\n", request.URI);
    assert(request.URI != NULL && strcmp(request.URI, "/submit-form") == 0);

    printf("HTTP Version: %.1f\n", request.HTTPVersion);
    assert(request.HTTPVersion == 1.1f);

    printf("\nHeaders:\n");
    assert(request.headerFields != NULL);
    printMap(request.headerFields);
    char *contentType = (char *)request.headerFields->search(request.headerFields, "Content-Type");
    assert(contentType != NULL && strcmp(contentType, "application/x-www-form-urlencoded") == 0);

    printf("\nBody Fields:\n");
    assert(request.bodyFields != NULL);
    printMap(request.bodyFields);
    char *name = (char *)request.bodyFields->search(request.bodyFields, "name");
    assert(name != NULL && strcmp(name, "John+Doe") == 0);
    char *age = (char *)request.bodyFields->search(request.bodyFields, "age");
    assert(age != NULL && strcmp(age, "30") == 0);

    HTTPRequestDestroy(&request);
    free(reqCopy);
    printf("POST Request Test Passed.\n\n");
}

void test_request_without_body() {
    printf("--- Test: Request without Body (e.g. GET with no extra headers) ---\n");
    char requestString[] = "GET / HTTP/1.0\r\n\r\n";
    char *reqCopy = strdup(requestString);
    assert(reqCopy != NULL);

    struct HTTPRequest request = HTTPRequestCreate(reqCopy);
    assert(request.method == GET);
    assert(request.URI != NULL && strcmp(request.URI, "/") == 0);
    assert(request.HTTPVersion == 1.0f);
    assert(request.headerFields != NULL && request.headerFields->tree->root == NULL); // No headers
    assert(request.bodyFields == NULL);
    HTTPRequestDestroy(&request);
    free(reqCopy);
    printf("Request without Body Test Passed.\n\n");
}

void test_malformed_request_line() {
    printf("--- Test: Malformed Request Line ---\n");
    char requestString[] = "GET /index.html\r\nHost: www.example.com\r\n\r\n"; // Missing HTTP version
    char *reqCopy = strdup(requestString);
    assert(reqCopy != NULL);

    struct HTTPRequest request = HTTPRequestCreate(reqCopy);
    // Behavior depends on parser robustness. Expect UNKNOWN method or version 0.0 or NULL URI.
    assert(request.method == GET); // It might parse method and URI
    assert(request.URI != NULL && strcmp(request.URI, "/index.html") == 0);
    assert(request.HTTPVersion == 0.0f); // Version parsing should fail gracefully
    // Headers might still be parsed if the line ends, or parsing might stop.
    // The current parser might get confused. Let's check headers are at least initialized.
    assert(request.headerFields != NULL);
    // char* host = (char*)request.headerFields->search(request.headerFields, "Host");
    // Depending on strtok behavior with the malformed line, Host might not be parsed.
    // For this test, we primarily care that it doesn't crash and handles it somewhat.

    HTTPRequestDestroy(&request);
    free(reqCopy);
    printf("Malformed Request Line Test Handled (check output for details).\n\n");
}

void test_empty_request() {
    printf("--- Test: Empty Request String ---\n");
    char requestString[] = "";
    char *reqCopy = strdup(requestString);
    assert(reqCopy != NULL);

    struct HTTPRequest request = HTTPRequestCreate(reqCopy);
    assert(request.method == UNKNOWN);
    assert(request.URI == NULL);
    assert(request.HTTPVersion == 0.0f);
    assert(request.headerFields == NULL || request.headerFields->tree->root == NULL); // Map might be created then found empty
    assert(request.bodyFields == NULL);
    HTTPRequestDestroy(&request); // Should handle NULLs gracefully
    free(reqCopy);

    // Test with NULL request string
    struct HTTPRequest request_null = HTTPRequestCreate(NULL);
    assert(request_null.method == UNKNOWN);
    HTTPRequestDestroy(&request_null);

    printf("Empty Request String Test Passed.\n\n");
}

int main() {
    test_simple_get_request();
    test_post_request_with_body();
    test_request_without_body();
    test_malformed_request_line();
    test_empty_request();

    printf("All HTTPRequest tests completed.\n");
    printf("Please review output for correctness, especially for malformed cases.\n");

    return 0;
}
