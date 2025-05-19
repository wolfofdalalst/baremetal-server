#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

struct listNode *createNode(void *data);
void destroyNode(struct listNode *node);

struct listNode *iterate(struct linkedList *list, int index);
void insertNode(struct linkedList *list, int index, void *data);
void removeNode(struct linkedList *list, int index);
void* getNode(struct linkedList *list, int index);

struct linkedList createLinkedList(void) {
    struct linkedList list;
    list.head = NULL;
    list.size = 0;
    list.insert = insertNode;
    list.remove = removeNode;
    list.get = getNode;
    return list;
}

struct listNode *createNode(void *data) {
    struct listNode *node = (struct listNode *)malloc(sizeof(struct listNode));
    if (node == NULL) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void destroyNode(struct listNode *node) {
    if (node != NULL) {
        free(node);
    }
}

struct listNode *iterate(struct linkedList *list, int index) {
    struct listNode *current = list->head;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    return current;
}

void insertNode(struct linkedList *list, int index, void *data) {
    if (index < 0 || index > list->size) {
        perror("Index out of bounds");
        exit(EXIT_FAILURE);
    }

    struct listNode *newNode = createNode(data);

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

void removeNode(struct linkedList *list, int index) {
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

    destroyNode(nodeToRemove);
    list->size--;
}

void* getNode(struct linkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        perror("Index out of bounds");
        exit(EXIT_FAILURE);
    }

    struct listNode *node = iterate(list, index);
    return node->data;
}