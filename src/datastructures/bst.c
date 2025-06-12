#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

// Creates a new BST node with given data
static struct listNode *createNode(void *data) {
    struct listNode *newNode = (struct listNode *)malloc(sizeof(struct listNode));
    if (!newNode) {
        perror("Failed to allocate memory for BST node");
        return NULL;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Searches for data in BST and returns pointer if found
void *searchBST(struct binarySearchTree *tree, void *data) {
    if (!tree || !tree->root) {
        return NULL;
    }
    struct listNode *current = tree->root;
    while (current != NULL) {
        int cmp = tree->compare(data, current->data);
        if (cmp == 0) {
            return current->data;
        }
        if (cmp < 0) {
            current = current->prev;
        } else {
            current = current->next;
        }
    }
    return NULL;
}

// Inserts new data into BST maintaining sorted order
void insertBST(struct binarySearchTree *tree, void *data) {
    if (!tree) {
        return;
    }
    struct listNode *newNode = createNode(data);
    if (!newNode) {
        return;
    }

    if (tree->root == NULL) {
        tree->root = newNode;
        return;
    }

    struct listNode *current = tree->root;
    struct listNode *parent = NULL;

    while (current != NULL) {
        parent = current;
        int cmp = tree->compare(data, current->data);
        if (cmp == 0) {
            free(newNode);
            return; 
        }
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

// Finds minimum value node in subtree
static struct listNode *findMin(struct listNode *node) {
    while (node && node->prev != NULL) {
        node = node->prev;
    }
    return node;
}

// Recursively removes node from BST
static struct listNode *removeNodeRecursive(struct listNode *root, void *data, int (*compare)(void *, void *), void **removedData) {
    if (root == NULL) return NULL;

    int cmp = compare(data, root->data);

    if (cmp < 0) {
        root->prev = removeNodeRecursive(root->prev, data, compare, removedData);
    } else if (cmp > 0) {
        root->next = removeNodeRecursive(root->next, data, compare, removedData);
    } else {
        if (*removedData == NULL) *removedData = root->data;

        if (root->prev == NULL) {
            struct listNode *temp = root->next;
            free(root);
            return temp;
        } else if (root->next == NULL) {
            struct listNode *temp = root->prev;
            free(root);
            return temp;
        }

        struct listNode *temp = findMin(root->next);
        root->data = temp->data;

        void* successorData = NULL;
        root->next = removeNodeRecursive(root->next, temp->data, compare, &successorData);
    }
    return root;
}

// Removes data from BST if found
void removeBST(struct binarySearchTree *tree, void *data) {
    if (!tree || !tree->root) {
        return;
    }
    void *removedData = NULL;
    tree->root = removeNodeRecursive(tree->root, data, tree->compare, &removedData);
}

// Creates new BST with comparison function
struct binarySearchTree *createBinarySearchTree(int (*compare)(void *a, void *b)) {
    struct binarySearchTree *tree = (struct binarySearchTree *)malloc(sizeof(struct binarySearchTree));
    if (!tree) {
        perror("Failed to allocate memory for BST");
        return NULL;
    }
    tree->root = NULL;
    tree->compare = compare;
    tree->search = searchBST;
    tree->insert = insertBST;
    tree->remove = removeBST;
    return tree;
}

// Recursively destroys all BST nodes
void destroyBSTHelper(struct listNode *node) {
    if (node == NULL) {
        return;
    }
    destroyBSTHelper(node->prev);
    destroyBSTHelper(node->next);
    free(node);
}

// Destroys BST and frees all memory
void destroyBinarySearchTree(struct binarySearchTree *tree) {
    if (tree == NULL) {
        return;
    }
    destroyBSTHelper(tree->root);
    free(tree);
}
