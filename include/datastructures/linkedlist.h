#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

struct linkedList {
    struct listNode *head;
    int size;

    void (*insert)(struct linkedList *list, int index, void *data, int size);
    void (*remove)(struct linkedList *list, int index);
    void *(*get)(struct linkedList *list, int index);
};

// Creates new linked list with initialized function pointers
struct linkedList *createLinkedList(void);

#endif  // LINKEDLIST_H