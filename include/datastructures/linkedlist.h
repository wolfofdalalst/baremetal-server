#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

struct linkedList {
    struct listNode *head;
    int size;

    void (*insert)(struct linkedList *list, int index, void *data);
    void (*remove)(struct linkedList *list, int index);
    void* (*get)(struct linkedList *list, int index);
};

struct linkedList createLinkedList(void);

#endif  // LINKEDLIST_H