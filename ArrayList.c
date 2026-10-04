#include "ArrayList.h"
#include "Move.h"
#include <stdlib.h>
#include <stddef.h>

void add(ArrayList* list, Move move){
    Node* toAdd = malloc(sizeof(Node));
    toAdd->move = move; // add the data to the node
    toAdd->next = NULL; // there is no next node
    toAdd->previous = list->last; // the previous node is the last node in the list
    list->last->next = toAdd; // the last node in the list is linked to the new node
    list->last = toAdd; // the last list in the node is the new toAdd list
    list->length++; // increase the size of the list
}

Node* dequeue(ArrayList* list){
    if (list == NULL || list->last == NULL){
        return NULL;
    }

    Node* toReturn = list->last;
    if (list->last != NULL){
        list->last->next = NULL;
    }

    list->last = toReturn->previous;
    toReturn->previous = NULL;
    list->length--;
    return toReturn;
}

void removeAny(ArrayList* list, Move move){
    if (list == NULL || list->first == NULL) return;
    for (Node* curr = list->first; curr != NULL; curr = curr->next){
        if (Moveequals(curr->move, move)){
            curr->previous->next = curr->next;
            curr->next->previous = curr->previous;
            curr->next = NULL;
            curr->previous = NULL;
        }
    }
}