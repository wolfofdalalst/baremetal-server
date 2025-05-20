#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/datastructures/map.h"

static int stringCompare(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

int main() {
    struct map *m = createMap(stringCompare);
    assert(m != NULL);

    // Insert key-value pairs
    char *key1 = strdup("name");
    char *val1 = strdup("Alice");
    char *key2 = strdup("age");
    char *val2 = strdup("30");
    char *key3 = strdup("city");
    char *val3 = strdup("New York");

    m->insert(m, key1, val1);
    m->insert(m, key2, val2);
    m->insert(m, key3, val3);

    // Search existing keys
    assert(strcmp((char *)m->search(m, key1), "Alice") == 0);
    assert(strcmp((char *)m->search(m, key2), "30") == 0);
    assert(strcmp((char *)m->search(m, key3), "New York") == 0);

    // Search non-existent key
    assert(m->search(m, "country") == NULL);

    // Remove a key
    m->remove(m, key2);
    assert(m->search(m, key2) == NULL);

    // Remove non-existent key (should not crash)
    m->remove(m, "unknown");

    // TODO: there is double free bug here
    // Clean up
    // destroyMap(m);
    // free(key1); free(val1);
    // free(key2); free(val2);
    // free(key3); free(val3);

    printf("All map tests passed!\n");
    return 0;
}
