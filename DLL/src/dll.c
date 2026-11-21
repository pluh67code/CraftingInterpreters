#include <stdlib.h>
#include <limits.h>
#include "dll.h"

typedef struct Node {
    char *string;
    struct Node *prev;
    struct Node *next;
} node;

typedef struct DLL {
    int size;
    node *head;
    node *tail;
} dll;


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

node *createNode(const char *str) {
    node *newnode = malloc(sizeof(node));
    if (newnode == NULL) {
        return NULL;
    }

    size_t len = strlen(str) + 1; 
    newnode->string = malloc(len);
    if (newnode->string == NULL) {
        free(newnode);
        return NULL;
    }
    strcpy(newnode->string, str);
    newnode->prev = NULL;
    newnode->next = NULL;
    return newnode;
}

typedef enum {
    INSERT_OK, INSERT_OUT_OF_BOUNDS, INSERT_FULL
} insertResult;

insertResult insertNode(dll *list, node *n, int spot) {
    if (list->size == INT_MAX) {
        return INSERT_FULL;
    }

    // size + 1 = insert
    if (spot <= 0 || spot > (list->size + 1)) {
        return INSERT_OUT_OF_BOUNDS;
    }

    if (list->size == 0) {
        list->head = n;
        list->tail = n;
    }
    else if (spot == (list->size + 1)) {
        list->tail->next = n;
        n->prev = list->tail;
        n->next = NULL;
        list->tail = n;
    }
    else { // insert somewhere in middle, 2 surrounding nodes
        node *curr = list->head;
        int currIndex = 1;
        while (currIndex != spot) {
            curr = curr->next;
            currIndex++;
        }
        
        node *prev = n->prev;
        prev->next = n;
        n->prev = prev;
        n->next = next;
        next->prev = n;
    }

    list->size++;
    return INSERT_OK;
}
