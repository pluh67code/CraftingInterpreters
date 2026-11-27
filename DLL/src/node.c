#include <stdlib.h>
#include <string.h>
#include "node.h"


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



