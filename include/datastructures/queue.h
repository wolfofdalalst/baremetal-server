#ifndef QUEUE_H
#define QUEUE_H

#include "linkedlist.h"

struct queue {
    struct linkedList *list;

    void (*push)(struct queue *queue, void *data, int size);
    void (*pop)(struct queue *queue);
    void *(*top)(struct queue *queue);
};

struct queue *createQueue(void);

#endif  // QUEUE_H