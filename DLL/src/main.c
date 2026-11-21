#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"

/*
define a doubly linked list of heap-allocated strings. 
Write functions to insert, find, and delete items from it. 
--
pointers
arrays and strings
structs and typedef
pointers II: arithmetic
mem alloc
multifile proj

[x, y, z, a, b, c]
d

*/

int main(void) {
    dll *mydll = createList();
    if (mydll == NULL) {
        fprintf(stderr, "Couldn't allocate dll\n");
        return EXIT_FAILURE;
    }
    // must de-alloc every node and dll, so make destroyList func
    return EXIT_SUCCESS;
}
