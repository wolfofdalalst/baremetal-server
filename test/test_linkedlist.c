#include <stdio.h>
#include <assert.h>
#include "../include/datastructures/linkedlist.h"

void test_linkedlist() {
    struct linkedListInt list = createLinkedList();

    // Test insert
    list.insert(&list, 0, 10);
    list.insert(&list, 1, 20);
    list.insert(&list, 1, 15);
    assert(list.size == 3);
    assert(list.get(&list, 0) == 10);
    assert(list.get(&list, 1) == 15);
    assert(list.get(&list, 2) == 20);

    // Test remove
    list.remove(&list, 1);
    assert(list.size == 2);
    assert(list.get(&list, 0) == 10);
    assert(list.get(&list, 1) == 20);

    // Test edge cases
    list.remove(&list, 0);
    list.remove(&list, 0);
    assert(list.size == 0);

    printf("All linked list tests passed!\n");
}

int main() {
    test_linkedlist();
    return 0;
}