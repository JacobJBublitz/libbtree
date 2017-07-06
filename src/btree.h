#ifndef LIBBTREE_BTREE_H
#define LIBBTREE_BTREE_H

#include <stdbool.h>

struct _btree;

typedef struct _btree_node {
    char *key;
    void *data;
    struct _btree_node *parent, *left, *right;
    struct _btree *tree;
} btree_node;

typedef enum _btree_error {
    BTREE_ERROR_NONE = 0,
    BTREE_ERROR_OUT_OF_MEMORY = 1,
    BTREE_ERROR_KEY_NOT_FOUND = 2,
    BTREE_ERROR_KEY_ALREADY_EXISTS = 3
} btree_error;

typedef struct _btree {
    btree_node *root;
} btree;

typedef void(*btree_foreach_proc_t)(const char *key, void *data, void *user);

btree_error btree_create(btree **tree);

void btree_destroy(btree *tree);

void btree_foreach(const btree *tree, btree_foreach_proc_t foreach_proc, void *user);

btree_error btree_insert(btree *tree, const char *key, void *data);

btree_error btree_remove(btree *tree, const char *key, void **data);

btree_error btree_search(const btree *tree, const char *key, void **data);

btree_error btree_node_create(btree_node **node, const char *key, void *data);

void btree_node_destroy(btree_node *node);

void btree_node_foreach(const btree_node *node, btree_foreach_proc_t foreach_proc, void *user);

btree_error btree_node_insert(btree_node *parent, btree_node *new_node);

btree_error btree_node_remove(btree_node *node, const char *key, void **data);

btree_error btree_node_search(const btree_node *parent, const char *key, void **data);

#endif