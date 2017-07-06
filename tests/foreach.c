#include <stdlib.h>

#include "common.h"

static int count = 0;

void foreach_proc(const char *key, void *data, void *user) {
    count++;
}

int main(void) {
    btree *tree;
    handle_error(btree_create(&tree));
    handle_error(btree_insert(tree, "Test1", (void *) 1));
    handle_error(btree_insert(tree, "Test0", (void *) 0));
    handle_error(btree_insert(tree, "Test2", (void *) 2));
    handle_error(btree_insert(tree, "Test3", (void *) 3));

    btree_foreach(tree, foreach_proc, NULL);

    if (count != 4) {
        handle_failure("btree_foreach");
    }

    btree_destroy(tree);
}