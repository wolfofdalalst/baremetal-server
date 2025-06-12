#include "map.h"
#include "node.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Global reference for BST comparison workaround
static struct map *currentMap = NULL;

// Adapts user key comparison for BST node structures
static int mapCompare(void *a, void *b) {
    struct listNode *nodeA = (struct listNode *)a;
    struct listNode *nodeB = (struct listNode *)b;
    
    if (!nodeA || !nodeB) return 0;
    if (!nodeA->key || !nodeB->key) return 0;
    
    if (currentMap && currentMap->userCompare) {
        return currentMap->userCompare(nodeA->key, nodeB->key);
    }
    
    return strcmp((char*)nodeA->key, (char*)nodeB->key);
}

// Inserts key-value pair into map
void insertMap(struct map *map, void *key, void *value) {
    if (!map || !map->tree) return;

    currentMap = map;

    struct listNode *newNode = (struct listNode *)malloc(sizeof(struct listNode));
    if (!newNode) {
        perror("Failed to allocate memory for map node");
        return;
    }
    newNode->key = key;
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;

    map->tree->insert(map->tree, newNode);
}

// Searches map for key and returns associated value
void *searchMap(struct map *map, void *key) {
    if (!map || !map->tree) return NULL;

    currentMap = map;

    struct listNode tempNode;
    tempNode.key = key;
    tempNode.data = NULL;
    tempNode.prev = NULL;
    tempNode.next = NULL;

    struct listNode *foundNode = (struct listNode *)map->tree->search(map->tree, &tempNode);

    if (foundNode) {
        return foundNode->data; 
    }
    return NULL;
}

// Removes key-value pair from map
void removeMap(struct map *map, void *key) {
    if (!map || !map->tree) return;

    currentMap = map;

    struct listNode tempNode;
    tempNode.key = key;

    struct listNode *nodeToRemove = (struct listNode *)map->tree->search(map->tree, &tempNode);

    if (nodeToRemove) {
        map->tree->remove(map->tree, nodeToRemove);
    } 
}

// Creates new map with comparison function
struct map *createMap(int (*compare)(void *a, void *b)) {
    if (compare == NULL) {
        fprintf(stderr, "Map creation requires a compare function.\n");
        return NULL;
    }

    struct map *newMap = (struct map *)malloc(sizeof(struct map));
    if (!newMap) {
        perror("Failed to allocate memory for map");
        return NULL;
    }

    newMap->userCompare = compare;

    newMap->tree = createBinarySearchTree(mapCompare);
    if (!newMap->tree) {
        free(newMap);
        perror("Failed to create BST for map");
        return NULL;
    }

    newMap->insert = insertMap;
    newMap->search = searchMap;
    newMap->remove = removeMap;

    return newMap;
}

// Destroys map and frees all memory
void destroyMap(struct map *map) {
    if (!map) return;

    if (map->tree) {
        destroyBinarySearchTree(map->tree);
    }
    free(map);
    currentMap = NULL;
}