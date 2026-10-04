#include "ArrayList.h"
#include "Move.h"
#include <stdlib.h>
#include <stddef.h>

void addToList(ArrayList* list, Move move){
    if (list == NULL) return;
    Node* toAdd = malloc(sizeof(Node));
    if (toAdd == NULL) return;
    toAdd->move = move; // add the data to the node
    toAdd->next = NULL; // there is no next node
    toAdd->previous = list->last; // the previous node is the last node in the list

    if (list->last != NULL){
        list->last->next = toAdd; // the last node in the list is linked to the new node
    } else {
        list->first = toAdd; // the last list in the node is the new toAdd list
    }
    list->last = toAdd;
    list->length++; // increase the size of the list
}

Node* dequeue(ArrayList* list){
    if (list == NULL || list->last == NULL){
        return NULL;
    }

    Node* toReturn = list->last;
    list->last = toReturn->previous;

    if (list->last != NULL){
        list->last->next = NULL;
    } else {
        list->first = NULL;
    }

    toReturn->previous = NULL;
    toReturn->next = NULL;
    list->length--;
    return toReturn;
}

void removeAny(ArrayList* list, Move move){
    if (list == NULL || list->first == NULL) return;
    for (Node* curr = list->first; curr != NULL; curr = curr->next){
        Node* next = curr->next;
        if (MoveEquals(curr->move, move)){
            if (curr->previous == NULL){ 
                list->first = next;
            } else {
                curr->previous->next = next;
            }
            if (next == NULL) {
                list->last = curr->previous;
            } else {
                next->previous = curr->previous;
            }
            curr->next = NULL;
            curr->previous = NULL;
            list->length--;
            return;
        }
    }
}