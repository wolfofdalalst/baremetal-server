#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>


struct nodeInt *createNodeInt(int value);
void destroyNodeInt(struct nodeInt *node);

struct nodeInt *iterate(struct linkedListInt *list, int index);
void insertNode(struct linkedListInt *list, int index, int value);
void removeNode(struct linkedListInt *list, int index);
int getNode(struct linkedListInt *list, int index);

struct linkedListInt createLinkedList(void) {
    struct linkedListInt list;
    list.head = NULL;
    list.size = 0;
    list.insert = insertNode;
    list.remove = removeNode;
    list.get = getNode;
    return list;
}

struct nodeInt *createNodeInt(int value) {
    struct nodeInt *node = (struct nodeInt *)malloc(sizeof(struct nodeInt));
    if (node == NULL) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = NULL;
    return node;
}

void destroyNodeInt(struct nodeInt *node) {
    if (node != NULL) {
        free(node);
    }
}

struct nodeInt *iterate(struct linkedListInt *list, int index) {
    struct nodeInt *current = list->head;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    return current;
}

void insertNode(struct linkedListInt *list, int index, int value) {
    if (index < 0 || index > list->size) {
        perror("Index out of bounds");
        exit(EXIT_FAILURE);
    }

    struct nodeInt *newNode = createNodeInt(value);

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        struct nodeInt *prevNode = iterate(list, index - 1);
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }

    list->size++;
}

void removeNode(struct linkedListInt *list, int index) {
    if (index < 0 || index >= list->size) {
        perror("Index out of bounds");
        exit(EXIT_FAILURE);
    }

    struct nodeInt *nodeToRemove;

    if (index == 0) {
        nodeToRemove = list->head;
        list->head = list->head->next;
    } else {
        struct nodeInt *prevNode = iterate(list, index - 1);
        nodeToRemove = prevNode->next;
        prevNode->next = nodeToRemove->next;
    }

    destroyNodeInt(nodeToRemove);
    list->size--;
}

int getNode(struct linkedListInt *list, int index) {
    if (index < 0 || index >= list->size) {
        perror("Index out of bounds");
        exit(EXIT_FAILURE);
    }

    struct nodeInt *node = iterate(list, index);
    return node->value;
}