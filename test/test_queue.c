#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../include/datastructures/queue.h"

void test_queue() {
    struct queue q = createQueue();

    // Test push
    int *val1 = malloc(sizeof(int));
    int *val2 = malloc(sizeof(int));
    int *val3 = malloc(sizeof(int));
    *val1 = 10;
    *val2 = 20;
    *val3 = 30;

    q.push(&q, val1);
    q.push(&q, val2);
    q.push(&q, val3);

    // Test top
    assert(*(int *)q.top(&q) == 10);

    // Test pop
    int *popped1 = (int *)q.pop(&q);
    assert(*popped1 == 10);
    free(popped1);

    int *popped2 = (int *)q.pop(&q);
    assert(*popped2 == 20);
    free(popped2);

    // Test top after pops
    assert(*(int *)q.top(&q) == 30);

    int *popped3 = (int *)q.pop(&q);
    assert(*popped3 == 30);
    free(popped3);

    // Test pop on empty queue
    assert(q.pop(&q) == NULL);

    printf("All queue tests passed!\n");
}

int main() {
    test_queue();
    return 0;
}