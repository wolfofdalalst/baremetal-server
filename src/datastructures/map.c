#include "map.h"
#include "node.h"
#include <stdlib.h>

static int (*userCompare)(void *, void *) = NULL;

static int mapCompare(void *a, void *b) {
    struct listNode *nodeA = (struct listNode *)a;
    struct listNode *nodeB = (struct listNode *)b;
    return userCompare(nodeA->key, nodeB->key);
}

void insertMap(struct map *map, void *key, void *value) {
    struct listNode *newNode = malloc(sizeof(struct listNode));
    if (!newNode) {
        return;
    }
    newNode->key = key;
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    map->tree->insert(map->tree, newNode);
}


void *searchMap(struct map *map, void *key) {
    struct listNode tempNode;
    tempNode.key = key;
    tempNode.data = NULL;

    struct listNode *node = map->tree->search(map->tree, &tempNode);
    if (node) {
        return node->data;
    }
    return NULL;
}

void removeMap(struct map *map, void *key) {
    struct listNode tempNode;
    tempNode.key = key;
    tempNode.data = NULL;

    struct listNode *node = map->tree->search(map->tree, &tempNode);
    if (node) {
        map->tree->remove(map->tree, node);
        listNodeDestroy(node);
    }
}


struct map *createMap(int (*compare)(void *a, void *b)) {
    userCompare = compare; 

    struct map *map = malloc(sizeof(struct map));
    if (!map) {
        return NULL;
    }

    map->tree = createBinarySearchTree(mapCompare);
    if (!map->tree) {
        free(map);
        return NULL;
    }

    map->insert = insertMap;
    map->search = searchMap;
    map->remove = removeMap;

    return map;
}


void destroyMap(struct map *map) {
    if (map) {
        destroyBinarySearchTree(map->tree);
        free(map);
    }
}