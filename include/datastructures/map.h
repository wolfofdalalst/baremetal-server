#ifndef MAP_H
#define MAP_H

#include "bst.h"

struct map {
    struct binarySearchTree *tree;

    void (*insert)(struct map *map, void *key, void *value);
    void *(*search)(struct map *map, void *key);
    void (*remove)(struct map *map, void *key);
};

struct map *createMap(int (*compare)(void *a, void *b));
void destroyMap(struct map *map);

#endif  // MAP_H