#ifndef NODE_H
#define NODE_H

typedef struct Node {
    char *string;
    struct Node *prev;
    struct Node *next;
} node;

node *createNode(const char *str);

#endif