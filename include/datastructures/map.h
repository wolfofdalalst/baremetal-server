#ifndef MAP_H
#define MAP_H

#include "bst.h"

struct map {
    struct binarySearchTree *tree;
    int (*userCompare)(void *a, void *b); // Store the comparison function per map instance

    void (*insert)(struct map *map, void *key, void *value);
    void *(*search)(struct map *map, void *key);
    void (*remove)(struct map *map, void *key);
};

// Creates new map with comparison function for keys
struct map *createMap(int (*compare)(void *a, void *b));

// Destroys map and frees all memory
void destroyMap(struct map *map);

#endif  // MAP_H