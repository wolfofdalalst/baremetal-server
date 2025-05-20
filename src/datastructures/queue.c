#include "queue.h"

#include <stdlib.h>

void push(struct queue *queue, void *data, int size);
void pop(struct queue *queue);
void *top(struct queue *queue);

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

void destroyQueue(struct queue *queue) {
    if (queue) {
        if (queue->list) {
            free(queue->list);
        }
        free(queue);
    }
}

void push(struct queue *queue, void *data, int size) {
    queue->list->insert(queue->list, queue->list->size, data, size);
}

void pop(struct queue *queue) {
    if (queue->list->size == 0) {
        return;
    }
    queue->list->remove(queue->list, 0);
}

void *top(struct queue *queue) {
    if (queue->list->size == 0) {
        return NULL;
    }
    return queue->list->get(queue->list, 0);
}