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

void removeBST(struct binarySearchTree *tree, void *data) {
    if (tree->root == NULL) {
        return;
    }

    struct listNode *current = tree->root;
    struct listNode *parent = NULL;

    // Find the node to remove
    while (current != NULL) {
        int cmp = tree->compare(data, current->data);
        if (cmp == 0) {
            break;
        }
        parent = current;
        if (cmp < 0) {
            current = current->prev;
        } else {
            current = current->next;
        }
    }

    if (current == NULL) {
        return;  // Node not found
    }

    // Case 1: Node has no children
    if (current->prev == NULL && current->next == NULL) {
        if (parent == NULL) {
            tree->root = NULL;
        } else if (parent->prev == current) {
            parent->prev = NULL;
        } else {
            parent->next = NULL;
        }
        free(current);
    }
    // Case 2: Node has one child
    else if (current->prev == NULL || current->next == NULL) {
        struct listNode *child =
            (current->prev != NULL) ? current->prev : current->next;

        if (parent == NULL) {
            tree->root = child;
        } else if (parent->prev == current) {
            parent->prev = child;
        } else {
            parent->next = child;
        }
        free(current);
    }
    // Case 3: Node has two children
    else {
        // Find the inorder successor (smallest in right subtree)
        struct listNode *successor = current->next;
        struct listNode *successorParent = current;

        while (successor->prev != NULL) {
            successorParent = successor;
            successor = successor->prev;
        }

        // Replace current's data with successor's data
        current->data = successor->data;

        // Remove the successor (which has at most one right child)
        if (successorParent->prev == successor) {
            successorParent->prev = successor->next;
        } else {
            successorParent->next = successor->next;
        }
        free(successor);
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
    tree->remove = removeBST;
    return tree;
}

void destroyBSTHelper(struct listNode *node) {
    if (node == NULL) {
        return;
    }
    destroyBSTHelper(node->prev);
    destroyBSTHelper(node->next);
    free(node);
}

void destroyBinarySearchTree(struct binarySearchTree *tree) {
    if (tree == NULL) {
        return;
    }
    destroyBSTHelper(tree->root);
    free(tree);
}
