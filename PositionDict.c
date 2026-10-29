#include "PositionDict.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

static inline uint64_t hash64(uint64_t x) {
    x ^= x >> 30;
    x *= 0xbf58476d1ce4e5b9ULL;
    x ^= x >> 27;
    x *= 0x94d049bb133111ebULL;
    x ^= x >> 31;
    return x;
}

void initDict(Dict* d, size_t capacity){
    d->table = calloc(capacity, sizeof *d->table);
    d->capacity = capacity;
    d->count = 0;
}

void freeDict(Dict* d){
    free(d->table);
    d->table = NULL;
    d->capacity = 0;
    d->count = 0;
}

void resize(Dict* d){
    size_t oldCapacity = d->capacity;
    DictNode* oldTable = d->table;

    d->capacity *= 2;
    d->table = calloc(d->capacity, sizeof *d->table);
    d->count = 0;

    for (size_t i = 0; i < oldCapacity; ++i){
        if (!oldTable[i].occupied) continue;

        size_t slot = (size_t)hash64(oldTable[i].position->hash%d->capacity);
        while (d->table[slot].occupied){
            slot = (slot + 1) % d->capacity;
        }

        d->table[slot] = oldTable[i];
        ++d->count;
    }
    free(oldTable);
}

void addPosition(TTentry* position, Dict* d){
    if (numOccurences(position->hash, d) == 0){ // if we haven't reached this position before
        size_t index = (size_t)hash64(position->hash)%(d->capacity);
        for (int i = index; i < d->capacity; i++){
            if (!d->table[i].occupied){ // the first empty slot starting from the wanted index
                d->table[i].position = position;
                d->table[i].occurences = 1;
            }
        } // if we make it out of the loop, we need to resize the list of stuff, but this hopefully won't happen
        resize(d);
        for (int i = index; i < d->capacity; i++){
            if (!d->table[i].occupied){ // the first empty slot starting from the wanted index
                d->table[i].position = position;
                d->table[i].occurences = 1;
                d->table[i].occupied = true;
            }
        }
    } else { // it's in the table... somewhere
        size_t index = (size_t)hash64(position->hash)%(d->capacity);
        for (int i = index; i < d->capacity; i++){
            if (d->table[i].position->hash == position->hash){
                d->table[i].occurences++;
            }
        }
    }
    
}

int numOccurences(uint64_t zobrist, Dict* d){
    size_t index = (size_t)hash64(zobrist)%(d->capacity);
    for (size_t i = 0; i < d->capacity; i++){
        size_t slot = (index + i) % d->capacity;
        DictNode* n = &d->table[slot];

        if (!n->occupied) return -1;
        if (n->position->hash == zobrist) return n->occurences;
    }
    return -1;
}

TTentry* getPosition(uint64_t zobrist, Dict* d){
    size_t index = (size_t)hash64(zobrist)%(d->capacity);
    for (size_t i = 0; i < d->capacity; i++){
        size_t slot = (index + i) % d->capacity;
        DictNode* n = &d->table[slot];

        if (n->position->hash == zobrist) return n->position;
    }
    return NULL;
}



