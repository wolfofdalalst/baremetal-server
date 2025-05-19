#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

enum HTTPMethod { GET, POST, PUT, DELETE, PATCH, OPTIONS, HEAD, TRACE };

struct HTTPRequest {
    enum HTTPMethod method;
    char *URI;
    float HTTPVersion;
};

struct HTTPRequest HTTPRequestCreate(char *requestString);

#endif  // HTTPREQUEST_H