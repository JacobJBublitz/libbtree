#include <stdlib.h>

#include "common.h"

int main(void) {
    btree *tree;
    handle_error(btree_create(&tree));

    char *data = "Test data";
    handle_error(btree_insert(tree, "Test", data));

    handle_error(btree_remove(tree, "Test", NULL));

    handle_error(btree_insert(tree, "Test2", &data[1]));

    void *test2_data;
    handle_error(btree_search(tree, "Test2", &test2_data));
    if (test2_data != &data[1]) {
        handle_failure("btree_search");
    }

    btree_destroy(tree);
}