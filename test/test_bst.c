#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/datastructures/bst.h"

int intCompare(void *a, void *b) {
    int intA = *(int *)a;
    int intB = *(int *)b;
    return intA - intB;
}

int main() {
    struct binarySearchTree *tree = createBinarySearchTree(intCompare);
    assert(tree != NULL);

    // Insert some integers
    int a = 10, b = 5, c = 15, d = 7;
    tree->insert(tree, &a);
    tree->insert(tree, &b);
    tree->insert(tree, &c);
    tree->insert(tree, &d);

    // Search for existing values
    int *result = (int *)tree->search(tree, &a);
    assert(result != NULL);
    assert(*result == 10);

    result = (int *)tree->search(tree, &b);
    assert(result != NULL);
    assert(*result == 5);

    result = (int *)tree->search(tree, &c);
    assert(result != NULL);
    assert(*result == 15);

    result = (int *)tree->search(tree, &d);
    assert(result != NULL);
    assert(*result == 7);

    // Search for a non-existent value
    int missing = 100;
    result = (int *)tree->search(tree, &missing);
    assert(result == NULL);

    printf("All binarySearchTree tests passed!\n");
    return 0;
}
