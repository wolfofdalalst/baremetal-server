#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/server.h"

void dummyLaunch(struct server *srv) {
    printf("Server launched with socket %d\n", srv->socket);
}

void test_serverCreate_success() {
    struct server srv = serverCreate(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8081,
                                     10, dummyLaunch);
    assert(srv.socket > 0);
    printf("Server created successfully with socket %d\n", srv.socket);
    close(srv.socket);  // Clean up
}

void test_serverCreate_fail() {
    // Invalid domain to trigger failure
    struct server srv =
        serverCreate(-1, SOCK_STREAM, 0, INADDR_ANY, 8081, 10, dummyLaunch);
    assert(srv.socket == -1);
    printf("Correctly failed to create server with invalid domain\n");
}

int main() {
    test_serverCreate_success();
    test_serverCreate_fail();
    printf("All server tests passed.\n");
    return 0;
}
