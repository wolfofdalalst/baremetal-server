#include "bst.h"

#include <stdlib.h>

void *searchBST(struct binarySearchTree *tree, void *data) {
    struct listNode *current = tree->root;
    while (current != NULL) {
        int cmp = tree->compare(data, current->data);
        if (cmp == 0) {
            return current->data;
        } else if (cmp < 0) {
            current = current->prev;
        } else {
            current = current->next;
        }
    }
    return NULL;
}

void insertBST(struct binarySearchTree *tree, void *data) {
    struct listNode *newNode = malloc(sizeof(struct listNode));
    if (!newNode) {
        return;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (tree->root == NULL) {
        tree->root = newNode;
        return;
    }

    struct listNode *current = tree->root;
    struct listNode *parent = NULL;

    while (current != NULL) {
        parent = current;
        int cmp = tree->compare(data, current->data);
        if (cmp < 0) {
            current = current->prev;
        } else {
            current = current->next;
        }
    }

    if (tree->compare(data, parent->data) < 0) {
        parent->prev = newNode;
    } else {
        parent->next = newNode;
    }
}

struct binarySearchTree *createBinarySearchTree(int (*compare)(void *a,
                                                               void *b)) {
    struct binarySearchTree *tree = malloc(sizeof(struct binarySearchTree));
    if (!tree) {
        return NULL;
    }
    tree->root = NULL;
    tree->compare = compare;
    tree->search = searchBST;
    tree->insert = insertBST;
    return tree;
}