#ifndef NODE_H
#define NODE_H

struct listNode {
    void *data;
    struct listNode *next;
    struct listNode *prev;
};

struct listNode *listNodeCreate(void *data, int size);
void listNodeDestroy(struct listNode *node);

#endif  // NODE_H
