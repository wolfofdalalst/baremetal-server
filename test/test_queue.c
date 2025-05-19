#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../include/datastructures/queue.h"

void test_queue() {
    struct queue *q = createQueue();
    assert(q != NULL);

    int a = 10, b = 20, c = 30;
    q->push(q, &a, sizeof(a));
    q->push(q, &b, sizeof(b));
    q->push(q, &c, sizeof(c));

    int *topVal = (int *)q->top(q);
    assert(topVal != NULL);
    assert(*topVal == 10);

    q->pop(q);
    topVal = (int *)q->top(q);
    assert(topVal != NULL);
    assert(*topVal == 20);

    q->pop(q);
    topVal = (int *)q->top(q);
    assert(topVal != NULL);
    assert(*topVal == 30);

    q->pop(q);
    topVal = (int *)q->top(q);
    assert(topVal == NULL);

    q->pop(q);
    assert(q->top(q) == NULL);

    printf("All tests passed!\n");
}

int main() {
    test_queue();
    return 0;
}
