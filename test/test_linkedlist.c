#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/datastructures/linkedlist.h"

// Tests linked list functionality
void test_linkedlist() {
    struct linkedList *list = createLinkedList();

    int *val1 = malloc(sizeof(int));
    int *val2 = malloc(sizeof(int));
    int *val3 = malloc(sizeof(int));
    *val1 = 10;
    *val2 = 20;
    *val3 = 15;

    list->insert(list, 0, val1, sizeof(int));
    list->insert(list, 1, val2, sizeof(int));
    list->insert(list, 1, val3, sizeof(int));

    assert(list->size == 3);
    assert(*(int *)list->get(list, 0) == 10);
    assert(*(int *)list->get(list, 1) == 15);
    assert(*(int *)list->get(list, 2) == 20);

    list->remove(list, 1);
    assert(list->size == 2);
    assert(*(int *)list->get(list, 0) == 10);
    assert(*(int *)list->get(list, 1) == 20);

    list->remove(list, 0);
    list->remove(list, 0);
    assert(list->size == 0);

    printf("All linked list tests passed!\n");
    free(val1);
    free(val2);
    free(val3);
}

int main() {
    test_linkedlist();
    return 0;
}