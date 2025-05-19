#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <node.h>

struct linkedListInt {
    struct nodeInt *head;
    int size;

    void (*insert)(struct linkedListInt *list, int index, int value);
    void (*remove)(struct linkedListInt *list, int index);
    int (*get)(struct linkedListInt *list, int index);
};

struct linkedListInt createLinkedList(void);

#endif  // LINKEDLIST_H