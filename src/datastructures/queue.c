#include "queue.h"

#include <stdlib.h>

void push(struct queue *queue, void *data, int size);
void pop(struct queue *queue);
void *top(struct queue *queue);

// Creates new queue with linked list backend
struct queue *createQueue(void) {
    struct queue *queue = (struct queue *)malloc(sizeof(struct queue));
    if (queue == NULL) {
        return NULL;
    }
    queue->list = createLinkedList();
    queue->push = push;
    queue->pop = pop;
    queue->top = top;
    return queue;
}

// Destroys queue and frees memory
void destroyQueue(struct queue *queue) {
    if (queue) {
        if (queue->list) {
            free(queue->list);
        }
        free(queue);
    }
}

// Pushes data to rear of queue
void push(struct queue *queue, void *data, int size) {
    queue->list->insert(queue->list, queue->list->size, data, size);
}

// Removes front element from queue
void pop(struct queue *queue) {
    if (queue->list->size == 0) {
        return;
    }
    queue->list->remove(queue->list, 0);
}

// Returns front element of queue without removing
void *top(struct queue *queue) {
    if (queue->list->size == 0) {
        return NULL;
    }
    return queue->list->get(queue->list, 0);
}