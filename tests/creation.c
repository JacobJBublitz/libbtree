#include <stdio.h>
#include <stdlib.h>

#include "common.h"

char *message = "Test Message";

int main(void) {
    btree *tree;
    btree_error error = btree_create(&tree, "Test", message);
    if (error != BTREE_ERROR_NONE) {
        fprintf(stderr, "libbtree failed on btree_create.\n");
        handle_error(error);
    }

    void *result;
    error = btree_search(tree, "Test", &result);
    if (error != BTREE_ERROR_NONE) {
        handle_error(error);
    }

    if (result != message) {
        fprintf(stderr, "libbtree failed on btree_search.\n");
        exit(EXIT_FAILURE);
    }

    btree_destroy(tree);
}