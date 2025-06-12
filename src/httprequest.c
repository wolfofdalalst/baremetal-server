#include "httprequest.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "datastructures/map.h"

// String comparison function for map data structures
static int stringCompare(void *a, void *b) { 
    return strcmp((char *)a, (char *)b); 
}

// Converts HTTP method string to enum value
enum HTTPMethod methodSelect(const char *method) {
    if (method == NULL) return UNKNOWN;
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

// Trims leading and trailing whitespace from string in-place
char *trim_space(char *str) {
    if (str == NULL) return NULL;
    char *end;

    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) 
        return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';

    return str;
}

// Parses HTTP request body into key-value pairs
struct map *parse_body(char *body_str, struct map *headers) {
    if (body_str == NULL || strlen(body_str) == 0) {
        return NULL; // No body to parse
    }

    struct map *bodyFields = createMap(stringCompare);
    if (!bodyFields) {
        perror("Failed to create map for body fields");
        return NULL;
    }

    // Example: For application/x-www-form-urlencoded
    // This is a very basic parser. Real-world parsing needs to handle URL decoding, etc.
    char *contentType = NULL;
    if(headers) {
        contentType = (char*)headers->search(headers, "Content-Type");
    }

    // Basic parsing for x-www-form-urlencoded
    if (contentType && strstr(contentType, "application/x-www-form-urlencoded")) {
        char *pair = strtok(body_str, "&");
        while (pair != NULL) {
            char *eq_ptr = strchr(pair, '=');
            if (eq_ptr != NULL) {
                *eq_ptr = '\0';
                char *key = strdup(pair);
                char *value = strdup(eq_ptr + 1);
                
                if(key && value){
                    bodyFields->insert(bodyFields, key, value);
                } else {
                    if(key) free(key);
                    if(value) free(value);
                }
            }
            pair = strtok(NULL, "&");
        }
    } else if (contentType && strstr(contentType, "application/json")) {
        fprintf(stderr, "JSON body parsing not implemented in this basic parser.\n");
    } else {
        fprintf(stderr, "Unsupported or unspecified body content type for parsing.\n");
    }

    if (bodyFields->tree->root == NULL) { // If no fields were added (e.g. parsing failed or empty body type)
        destroyMap(bodyFields);
        return NULL;
    }

    return bodyFields;
}

// Creates HTTPRequest structure from raw request string
struct HTTPRequest HTTPRequestCreate(char *requestString) {
    struct HTTPRequest request;
    memset(&request, 0, sizeof(struct HTTPRequest));
    request.headerFields = createMap(stringCompare);
    if (!request.headerFields) {
        perror("Failed to create map for header fields");
        request.method = UNKNOWN;
        return request;
    }

    if (requestString == NULL) {
        request.method = UNKNOWN;
        return request;
    }
    
    char *requestCopy = strdup(requestString);
    if (!requestCopy) {
        perror("Failed to duplicate request string");
        request.method = UNKNOWN;
        destroyMap(request.headerFields);
        request.headerFields = NULL;
        return request;
    }
    
    char *lines[100];
    int lineCount = 0;
    char *line_start = requestCopy;
    char *line_end;
    
    while ((line_end = strstr(line_start, "\r\n")) != NULL) {
        *line_end = '\0';
        lines[lineCount++] = line_start;
        line_start = line_end + 2;
        if (lineCount >= 99) break;
    }
    
    if (lineCount == 0) {
        request.method = UNKNOWN;
        destroyMap(request.headerFields);
        request.headerFields = NULL;
        free(requestCopy);
        return request;
    }

    char *current_line = lines[0];
    char *method_str = strtok(current_line, " ");
    char *uri_str = strtok(NULL, " ");
    char *version_str = strtok(NULL, " ");

    if (method_str) request.method = methodSelect(method_str);
    else request.method = UNKNOWN;

    if (uri_str) request.URI = strdup(uri_str);
    else request.URI = NULL;

    if (version_str && strncmp(version_str, "HTTP/", 5) == 0) {
        request.HTTPVersion = atof(version_str + 5);
    } else {
        request.HTTPVersion = 0.0;
    }

    for (int i = 1; i < lineCount; i++) {
        current_line = lines[i];
        if (strlen(current_line) == 0) {
            break;
        }
        
        char *colon_ptr = strchr(current_line, ':');
        if (colon_ptr != NULL) {
            *colon_ptr = '\0';
            char *header_name = strdup(current_line);
            char *header_value = strdup(trim_space(colon_ptr + 1));

            if(header_name && header_value){
                request.headerFields->insert(request.headerFields, header_name, header_value);
            } else {
                if(header_name) free(header_name);
                if(header_value) free(header_value);
            }
        }
    }

    char *body_start = NULL;
    if (requestString) {
        char *header_end_marker = strstr(requestString, "\r\n\r\n");
        if (header_end_marker) {
            body_start = header_end_marker + 4;
        } else {
            header_end_marker = strstr(requestString, "\n\n");
            if (header_end_marker) {
                 body_start = header_end_marker + 2;
            }
        }
    }

    if (body_start && strlen(body_start) > 0) {
        char *body_copy = strdup(body_start);
        if (body_copy) {
            request.bodyFields = parse_body(body_copy, request.headerFields);
            free(body_copy);
        } else {
            perror("Failed to duplicate body for parsing");
        }
    } else {
        request.bodyFields = NULL;
    }
    
    free(requestCopy);
    
    return request;
}

// Destroys HTTPRequest and frees all allocated memory
void HTTPRequestDestroy(struct HTTPRequest *request) {
    if (request == NULL) return;

    if (request->URI) {
        free(request->URI);
        request->URI = NULL;
    }

    if (request->headerFields) {
        destroyMap(request->headerFields); 
        request->headerFields = NULL;
    }

    if (request->bodyFields) {
        destroyMap(request->bodyFields);
        request->bodyFields = NULL;
    }
}
