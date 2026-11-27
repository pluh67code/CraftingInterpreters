#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "dll.h"


dll *createList(void) {
    dll *newdll = malloc(sizeof(dll));
    if (newdll == NULL) {
        return NULL;
    }
    newdll->size = 0;
    newdll->head = NULL;
    newdll->tail = NULL;
    return newdll;
}

void deleteList(dll *list) {
    node *curr = list->head;

    while (curr != NULL) {
        node *next = curr->next;
        free(curr->string);
        free(curr);
        curr = next;
    }

    free(list);
}

insertResult insertNode(dll *list, node *n, int spot) {
    if (list->size == INT_MAX) {
        return INSERT_FULL;
    }

    // size + 1 = append
    if (spot <= 0 || spot > (list->size + 1)) {
        return INSERT_OUT_OF_BOUNDS;
    }

    if (list->size == 0) {
        n->prev = NULL;
        n->next = NULL;
        list->head = n;
        list->tail = n;
    }
    else if (spot == (list->size + 1)) {
        list->tail->next = n;
        n->prev = list->tail;
        n->next = NULL;
        list->tail = n;
    }
    else if (spot == 1) {
        n->prev = NULL;
        n->next = list->head;
        list->head->prev = n;
        list->head = n;
    }
    else {
        node *curr = list->head;
        int currIndex = 1;
        while (currIndex != spot) {
            curr = curr->next;
            currIndex++;
        }
        node *prev = curr->prev;
        
        prev->next = n;
        curr->prev = n;
        n->prev = prev;
        n->next = curr;
        
    }

    list->size++;
    return INSERT_OK;
}

node *findNode(dll *list, const char *string) {
    node *curr = list->head;

    while (curr != NULL && strcmp(string, curr->string) != 0) {
        curr = curr->next;
    }

    return curr;
}

bool deleteNode(dll *list, const char *string) {
    node *curr = findNode(list, string);
    if (curr == NULL) return false;

    node *prev = curr->prev;
    node *next = curr->next;

    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    }
    else if (prev == NULL) {
        next->prev = NULL;
        list->head = next;
    }
    else if (next == NULL) {
        prev->next = NULL;
        list->tail = prev;
    }
    else {
        prev->next = next;
        next->prev = prev;
    }

    free(curr->string);
    free(curr);
    list->size--;
    return true;
}

