#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"
#include "node.h"
/*
Claude made these tests btw
*/


static int failures = 0;

// Prints the list forwards and backwards, e.g. "[a b c] / [c b a] (size 3)"
static void printList(const dll *list) {
    printf("[");
    for (node *n = list->head; n != NULL; n = n->next) {
        printf("%s%s", n->string, n->next ? " " : "");
    }
    printf("] / [");
    for (node *n = list->tail; n != NULL; n = n->prev) {
        printf("%s%s", n->string, n->prev ? " " : "");
    }
    printf("] (size %d)\n", list->size);
}

// Checks the list matches `expected` (space-separated, "" for empty)
// walking forwards AND backwards, and that size/head/tail are consistent.
static void check(const char *label, const dll *list, const char *expected) {
    char fwd[256] = "", bwd[256] = "";
    int count = 0;

    for (node *n = list->head; n != NULL; n = n->next) {
        if (count++) strcat(fwd, " ");
        strcat(fwd, n->string);
    }

    // walk backwards from tail, prepending, so it should read the same as fwd
    for (node *n = list->tail; n != NULL; n = n->prev) {
        char tmp[256];
        snprintf(tmp, sizeof tmp, "%s%s%s", n->string, bwd[0] ? " " : "", bwd);
        strcpy(bwd, tmp);
    }

    int ok = strcmp(fwd, expected) == 0
          && strcmp(bwd, expected) == 0
          && count == list->size
          && (list->size == 0) == (list->head == NULL)
          && (list->size == 0) == (list->tail == NULL);

    printf("%s %-28s ", ok ? "PASS" : "FAIL", label);
    printList(list);
    if (!ok) {
        printf("     expected: [%s]\n", expected);
        failures++;
    }
}

static void expect(const char *label, int ok) {
    printf("%s %s\n", ok ? "PASS" : "FAIL", label);
    if (!ok) failures++;
}

// Creates a node and inserts it; frees it if the insert is rejected.
static insertResult insert(dll *list, const char *s, int spot) {
    node *n = createNode(s);
    if (n == NULL) {
        fprintf(stderr, "createNode failed\n");
        exit(EXIT_FAILURE);
    }
    insertResult r = insertNode(list, n, spot);
    if (r != INSERT_OK) {
        free(n->string);
        free(n);
    }
    return r;
}

int main(void) {
    dll *mydll = createList();
    if (mydll == NULL) {
        fprintf(stderr, "Couldn't allocate dll\n");
        return EXIT_FAILURE;
    }

    printf("--- insert ---\n");
    check("empty list", mydll, "");
    insert(mydll, "b", 1);       check("insert into empty", mydll, "b");
    insert(mydll, "d", 2);       check("append (tail)", mydll, "b d");
    insert(mydll, "a", 1);       check("insert at head", mydll, "a b d");
    insert(mydll, "c", 3);       check("insert in middle", mydll, "a b c d");
    insert(mydll, "e", 5);       check("append again", mydll, "a b c d e");

    expect("spot 0 is out of bounds",
           insert(mydll, "x", 0) == INSERT_OUT_OF_BOUNDS);
    expect("spot size+2 is out of bounds",
           insert(mydll, "x", mydll->size + 2) == INSERT_OUT_OF_BOUNDS);
    check("unchanged after bad inserts", mydll, "a b c d e");

    printf("--- find ---\n");
    node *found = findNode(mydll, "c");
    expect("find existing \"c\"", found != NULL && strcmp(found->string, "c") == 0);
    expect("find missing returns NULL", findNode(mydll, "zzz") == NULL);

    printf("--- delete ---\n");
    deleteNode(mydll, "zzz");    check("delete missing (no-op)", mydll, "a b c d e");
    deleteNode(mydll, "c");      check("delete middle", mydll, "a b d e");
    deleteNode(mydll, "a");      check("delete head", mydll, "b d e");
    deleteNode(mydll, "e");      check("delete tail", mydll, "b d");
    deleteNode(mydll, "b");      check("delete head again", mydll, "d");
    deleteNode(mydll, "d");      check("delete only node", mydll, "");
    deleteNode(mydll, "d");      check("delete from empty", mydll, "");
    expect("find on empty returns NULL", findNode(mydll, "a") == NULL);

    printf("--- reuse after emptying ---\n");
    insert(mydll, "x", 1);       check("insert after emptying", mydll, "x");
    insert(mydll, "y", 2);       check("append after emptying", mydll, "x y");

    // nodes left in the list on purpose, so deleteList has something to free
    deleteList(mydll);
    mydll = NULL;

    printf("\n%s (%d failure%s)\n", failures ? "SOME TESTS FAILED" : "ALL TESTS PASSED",
           failures, failures == 1 ? "" : "s");
    return failures ? EXIT_FAILURE : EXIT_SUCCESS;
}
