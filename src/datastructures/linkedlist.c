#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

struct listNode *iterate(struct linkedList *list, int index);
void insert(struct linkedList *list, int index, void *data, int size);
void removeAtIndex(struct linkedList *list, int index);
void *get(struct linkedList *list, int index);

struct linkedList *createLinkedList(void) {
    struct linkedList *list =
        (struct linkedList *)malloc(sizeof(struct linkedList));
    if (list == NULL) {
        perror("Failed to allocate memory for linked list");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->size = 0;
    list->insert = insert;
    list->remove = removeAtIndex;
    list->get = get;
    return list;
}

struct listNode *iterate(struct linkedList *list, int index) {
    struct listNode *current = list->head;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    return current;
}

void insert(struct linkedList *list, int index, void *data, int size) {
    if (index < 0 || index > list->size) {
        perror("Index out of bounds");
        exit(EXIT_FAILURE);
    }

    struct listNode *newNode = listNodeCreate(data, size);

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        struct listNode *prevNode = iterate(list, index - 1);
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }

    list->size++;
}

void removeAtIndex(struct linkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        perror("Index out of bounds");
        exit(EXIT_FAILURE);
    }

    struct listNode *nodeToRemove;

    if (index == 0) {
        nodeToRemove = list->head;
        list->head = list->head->next;
    } else {
        struct listNode *prevNode = iterate(list, index - 1);
        nodeToRemove = prevNode->next;
        prevNode->next = nodeToRemove->next;
    }

    listNodeDestroy(nodeToRemove);
    list->size--;
}

void *get(struct linkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        perror("Index out of bounds");
        exit(EXIT_FAILURE);
    }

    struct listNode *node = iterate(list, index);
    return node->data;
}