#ifndef DLL_H
#define DLL_H
#include "node.h"

typedef struct DLL {
    int size;
    node *head;
    node *tail;
} dll;

typedef enum {
    INSERT_OK, INSERT_OUT_OF_BOUNDS, INSERT_FULL
} insertResult;


dll *createList(void);
void deleteList(dll *list);
insertResult insertNode(dll *list, node *n, int spot);
bool deleteNode(dll *list, const char *string);
node *findNode(dll *list, const char *string);

#endif