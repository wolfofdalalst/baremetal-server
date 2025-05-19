#ifndef BST_H
#define BST_H

#include "node.h"

struct binarySearchTree {
    struct listNode *root;
    int (*compare)(void *a, void *b);
    void *(*search)(struct binarySearchTree *tree, void *data);
    void (*insert)(struct binarySearchTree *tree, void *data);
};

struct binarySearchTree *createBinarySearchTree(int (*compare)(void *a,
                                                               void *b));

#endif  // BST_H