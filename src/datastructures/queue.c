#include "queue.h"

#include <stdlib.h>

void pushQueue(struct queue *queue, void *data);
void *popQueue(struct queue *queue);
void *topQueue(struct queue *queue);

struct queue createQueue(void) {
    struct queue queue;
    queue.list = createLinkedList();
    queue.push = &pushQueue;
    queue.pop = &popQueue;
    queue.top = &topQueue;
    return queue;
}

void pushQueue(struct queue *queue, void *data) {
    queue->list.insert(&queue->list, queue->list.size, data);
}

void *popQueue(struct queue *queue) {
    if (queue->list.size == 0) {
        return NULL;
    }
    void *data = queue->list.get(&queue->list, 0);
    queue->list.remove(&queue->list, 0);
    return data;
}

void *topQueue(struct queue *queue) {
    if (queue->list.size == 0) {
        return NULL;
    }
    return queue->list.get(&queue->list, 0);
}