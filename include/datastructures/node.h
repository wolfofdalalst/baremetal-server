#ifndef NODE_H
#define NODE_H

struct listNode {
    void* key;
    void *data;
    struct listNode *next;
    struct listNode *prev;
};

// Creates new list node with copied data
struct listNode *listNodeCreate(void *data, int size);

// Destroys node and frees allocated memory
void listNodeDestroy(struct listNode *node);

#endif  // NODE_H
