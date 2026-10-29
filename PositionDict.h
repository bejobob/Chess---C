#ifndef DICT_H
#define DICT_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "TTentry.h"

typedef struct DictNode{
    TTentry* position;
    int occurences;
    bool occupied;
} DictNode;

typedef struct Dict{
    DictNode* table;
    size_t capacity;
    size_t count;
} Dict;

void addPosition(TTentry* position, Dict* d);
int numOccurences(uint64_t zobrist, Dict* d);
TTentry* getPosition(uint64_t zobrist, Dict* d);
void initDict(Dict* d, size_t capacity);
void freeDict(Dict* d);
void resize(Dict* d);

static inline uint64_t hash64(uint64_t zobrist);

#endif