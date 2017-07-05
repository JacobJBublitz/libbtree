#include <stdlib.h>

#include "common.h"

int main(void) {
    btree *tree;
    handle_error(btree_create(&tree, "Test", NULL));

    handle_error(btree_insert(tree, "Test1", (void *) 1));
    handle_error(btree_insert(tree, "Test2", (void *) 2));

    void *result;
    handle_error(btree_search(tree, "Test2", &result));
    if (result != (void *) 2) {
        handle_failure("btree_search");
    }

    handle_error(btree_remove(tree, "Test", NULL));

    handle_error(btree_search(tree, "Test1", &result));
    if (result != (void *) 1) {
        handle_failure("btree_search");
    }

    btree_destroy(tree);
}