#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/datastructures/bst.h"

// Integer comparison function for BST
int intCompare(void *a, void *b) {
    int intA = *(int *)a;
    int intB = *(int *)b;
    if (intA < intB) return -1;
    if (intA > intB) return 1;
    return 0;
}

// Frees integer data allocated for tests
void free_int_data(void* data) {
    free(data);
}

// Main BST test function
int main() {
    struct binarySearchTree *tree = createBinarySearchTree(intCompare);
    assert(tree != NULL);
    printf("BST created successfully.\n");

    int *a = malloc(sizeof(int)); *a = 10;
    int *b = malloc(sizeof(int)); *b = 5;
    int *c = malloc(sizeof(int)); *c = 15;
    int *d = malloc(sizeof(int)); *d = 7;
    int *e = malloc(sizeof(int)); *e = 3;
    int *f = malloc(sizeof(int)); *f = 12;
    int *g = malloc(sizeof(int)); *g = 17;

    printf("Inserting 10...\n");
    tree->insert(tree, a);
    printf("Inserting 5...\n");
    tree->insert(tree, b);
    printf("Inserting 15...\n");
    tree->insert(tree, c);
    printf("Inserting 7...\n");
    tree->insert(tree, d);
    printf("Inserting 3...\n");
    tree->insert(tree, e);
    printf("Inserting 12...\n");
    tree->insert(tree, f);
    printf("Inserting 17...\n");
    tree->insert(tree, g);

    printf("Insertion complete.\n");

    // Search for existing values
    int search_val = 10;
    int *result = (int *)tree->search(tree, &search_val);
    assert(result != NULL && *result == 10);
    printf("Found 10.\n");

    search_val = 5;
    result = (int *)tree->search(tree, &search_val);
    assert(result != NULL && *result == 5);
    printf("Found 5.\n");

    search_val = 15;
    result = (int *)tree->search(tree, &search_val);
    assert(result != NULL && *result == 15);
    printf("Found 15.\n");

    search_val = 7;
    result = (int *)tree->search(tree, &search_val);
    assert(result != NULL && *result == 7);
    printf("Found 7.\n");

    // Search for a non-existent value
    int missing = 100;
    result = (int *)tree->search(tree, &missing);
    assert(result == NULL);
    printf("Correctly did not find 100.\n");

    // Test remove
    printf("Removing 7 (node with one child or leaf)...\n");
    int val_to_remove = 7;
    tree->remove(tree, &val_to_remove);
    result = (int *)tree->search(tree, &val_to_remove);
    assert(result == NULL);
    printf("7 removed. Search for 7: %s\n", result ? "Found" : "Not found");
    // Verify other elements still exist
    search_val = 5;
    result = (int *)tree->search(tree, &search_val);
    assert(result != NULL && *result == 5);

    printf("Removing 5 (node with one child or leaf)...\n");
    val_to_remove = 5;
    tree->remove(tree, &val_to_remove);
    result = (int *)tree->search(tree, &val_to_remove);
    assert(result == NULL);
    printf("5 removed. Search for 5: %s\n", result ? "Found" : "Not found");
    search_val = 3;
    result = (int *)tree->search(tree, &search_val);
    assert(result != NULL && *result == 3);
    search_val = 10;
    result = (int *)tree->search(tree, &search_val);
    assert(result != NULL && *result == 10);

    printf("Removing 15 (node with two children)...\n");
    val_to_remove = 15;
    tree->remove(tree, &val_to_remove);
    result = (int *)tree->search(tree, &val_to_remove);
    assert(result == NULL);
    printf("15 removed. Search for 15: %s\n", result ? "Found" : "Not found");
    // Check structure integrity by searching for remaining elements
    search_val = 12;
    result = (int *)tree->search(tree, &search_val);
    assert(result != NULL && *result == 12);
    search_val = 17;
    result = (int *)tree->search(tree, &search_val);
    assert(result != NULL && *result == 17);

    printf("Removing 10 (root node)...\n");
    val_to_remove = 10;
    tree->remove(tree, &val_to_remove);
    result = (int *)tree->search(tree, &val_to_remove);
    assert(result == NULL);
    printf("10 removed. Search for 10: %s\n", result ? "Found" : "Not found");
    // Check remaining elements
    // The new root could be 3 or 12 depending on specific successor/predecessor logic for root removal
    // Let's just check if remaining elements are findable
    search_val = 3;
    result = (int *)tree->search(tree, &search_val);
    assert(result != NULL && *result == 3);
    search_val = 12;
    result = (int *)tree->search(tree, &search_val);
    assert(result != NULL && *result == 12);
    search_val = 17;
    result = (int *)tree->search(tree, &search_val);
    assert(result != NULL && *result == 17);

    // Clean up: destroy the tree
    // Before destroying the tree, we must free the dynamically allocated integer data
    // The BST itself only frees the node structures, not the data they point to.
    // This requires iterating the tree or knowing what was inserted.
    // For this test, we have pointers a,b,c,d,e,f,g. Some were removed.
    // The ones remaining in the tree are: e (3), f (12), g (17). (Original pointers)
    // The data for a,b,c,d was removed from tree structure, but memory for *a, *b, *c, *d needs freeing if not handled by remove.
    // The current removeBST does not free the user data, it returns it via a parameter.
    // So, we need to free a, b, c, d, e, f, g manually.
    
    destroyBinarySearchTree(tree);
    printf("BST destroyed.\n");

    // Free the data that was inserted
    free(a); free(b); free(c); free(d); free(e); free(f); free(g);
    printf("Dynamically allocated test data freed.\n");

    printf("All BST tests passed!\n");
    return 0;
}
