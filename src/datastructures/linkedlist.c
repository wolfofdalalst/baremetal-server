#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

// Function prototypes for internal operations
struct listNode *iterate(struct linkedList *list, int index);
void insert(struct linkedList *list, int index, void *data, int size);
void removeAtIndex(struct linkedList *list, int index);
void *get(struct linkedList *list, int index);

// Creates new linked list with initialized function pointers
struct linkedList *createLinkedList(void) {
    struct linkedList *list =
        (struct linkedList *)malloc(sizeof(struct linkedList));
    if (list == NULL) {
        perror("Failed to allocate memory for linked list");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    list->insert = insert;
    list->remove = removeAtIndex;
    list->get = get;
    return list;
}

// Iterates to node at specified index
struct listNode *iterate(struct linkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        return NULL;
    }
    struct listNode *current = list->head;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    return current;
}

// Inserts data at specified index in linked list
void insert(struct linkedList *list, int index, void *data, int size) {
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Index out of bounds for insert\\n");
        return;
    }

    struct listNode *newNode = listNodeCreate(data, size);
    if (newNode == NULL) {
        perror("Failed to create node for linked list insert");
        return;
    }

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        struct listNode *prevNode = iterate(list, index - 1);
        if (prevNode != NULL) {
            newNode->next = prevNode->next;
            prevNode->next = newNode;
        } else {
            fprintf(stderr, "Failed to find previous node for insert\\n");
            listNodeDestroy(newNode);
            return;
        }
    }
    list->size++;
}

// Removes node at specified index
void removeAtIndex(struct linkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Index out of bounds for remove\\n");
        return;
    }

    struct listNode *nodeToRemove = NULL;
    if (index == 0) {
        nodeToRemove = list->head;
        list->head = list->head->next;
    } else {
        struct listNode *prevNode = iterate(list, index - 1);
        if (prevNode != NULL && prevNode->next != NULL) {
            nodeToRemove = prevNode->next;
            prevNode->next = nodeToRemove->next;
        } else {
            fprintf(stderr, "Failed to find node for remove\\n");
            return;
        }
    }

    if (nodeToRemove != NULL) {
        listNodeDestroy(nodeToRemove);
    }
    list->size--;
}

// Returns data at specified index
void *get(struct linkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "Index out of bounds for get\\n");
        return NULL;
    }
    struct listNode *node = iterate(list, index);
    if (node != NULL) {
        return node->data;
    }
    return NULL;
}