#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "datastructures/map.h"

enum HTTPMethod {
    GET,
    POST,
    PUT,
    DELETE,
    PATCH,
    OPTIONS,
    HEAD,
    TRACE,
    UNKNOWN
};

struct HTTPRequest {
    enum HTTPMethod method;
    char *URI;
    float HTTPVersion;
    struct map *headerFields;
    struct map *bodyFields;
};

struct HTTPRequest HTTPRequestCreate(char *requestString);
void HTTPRequestDestroy(struct HTTPRequest *request);

#endif  // HTTPREQUEST_H