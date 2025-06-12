#ifndef QUEUE_H
#define QUEUE_H

#include "linkedlist.h"

struct queue {
    struct linkedList *list;

    void (*push)(struct queue *queue, void *data, int size);
    void (*pop)(struct queue *queue);
    void *(*top)(struct queue *queue);
};

// Creates new queue with linked list backend
struct queue *createQueue(void);

// Destroys queue and frees memory
void destroyQueue(struct queue *queue);

#endif  // QUEUE_H