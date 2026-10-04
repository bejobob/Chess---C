#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "Move.h"
typedef struct Node{
    Move move;
    Node* next;
    Node* previous; // TODO: do I need this? I don't think I ever go back...
}Node;
typedef struct LinkedList_Move{
    Node* first;
    Node* last; // TODO: do I need this?
    int length;
} ArrayList;

void add(ArrayList* list, Move move);
Node* dequeue(ArrayList* list);
void removeAny(ArrayList* list, Move move);
#endif