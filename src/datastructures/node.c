#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creates new list node with copied data
struct listNode *listNodeCreate(void *data, int size) {
    struct listNode *node = malloc(sizeof(struct listNode));
    if (node == NULL) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    node->data = malloc(size);
    if (node->data == NULL) {
        perror("Failed to allocate memory for node data");
        free(node);
        exit(EXIT_FAILURE);
    }
    memcpy(node->data, data, size);
    node->next = NULL;
    return node;
}

// Destroys node and frees allocated memory
void listNodeDestroy(struct listNode *node) {
    if (node != NULL) {
        free(node->data);
        free(node);
    }
}