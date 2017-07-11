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

/**
 * Create a new btree.
 * @param[out] tree Where to store the created btree.
 */
btree_error btree_create(btree **tree);

/**
 * Destroy a btree.
 * @param[in] tree The tree to destroy.
 */
void btree_destroy(btree *tree);

/**
 * Execute a function on all nodes of a tree.
 * @param[in] tree         The tree to execute the funcion on.
 * @param[in] foreach_proc The function to execute.
 * @param[in] user         A user defined value passed to foreach_proc.
 */
void btree_foreach(const btree *tree, btree_foreach_proc_t foreach_proc, void *user);

/**
 * Add a new node to a btree.
 * @param[in] tree The tree to add the node to.
 * @param[in] key  The node's key.
 * @param[in] data The node's value.
 */
btree_error btree_insert(btree *tree, const char *key, void *data);

/**
 * Remove a node from a btree.
 * @param[in]  tree The tree of the node to remove.
 * @param[in]  key  The node's key.
 * @param[out] data The node's data.
 */
btree_error btree_remove(btree *tree, const char *key, void **data);

/**
 * Search a btree for a node.
 * @param[in]  tree The tree to search
 * @param[in]  key  The node's key.
 * @param[out] data The node's data.
 */
btree_error btree_search(const btree *tree, const char *key, void **data);

/**
 * Create a new node.
 * @param[out] node Where to store the node.
 * @param[in]  key  The node's key.
 * @param[in]  data the node's data.
 * @return
 */
btree_error btree_node_create(btree_node **node, const char *key, void *data);

/**
 * Destroy a node.
 * @param[in] node The node to destroy.
 */
void btree_node_destroy(btree_node *node);

/**
 * Execute a function on this node and all its children.
 * @param[in] node         The node to execute on.
 * @param[in] foreach_proc The function to execute.
 * @param[in] user         A user defined value passed to foreach_proc.
 */
void btree_node_foreach(const btree_node *node, btree_foreach_proc_t foreach_proc, void *user);

/**
 * Insert a node as a child of a parent node.
 * @param[in] parent   The parent node.
 * @param[in] new_node The node to insert.
 */
btree_error btree_node_insert(btree_node *parent, btree_node *new_node);

/**
 * Remove a child node from a parent node.
 * @param[in]  node The parent node.
 * @param[in]  key  The key of the node to remove.
 * @param[out] data The data pointer the removed node had.
 */
btree_error btree_node_remove(btree_node *node, const char *key, void **data);

/**
 * Search for a child node of a parent node.
 * @param[in]  parent The parent node.
 * @param[in]  key    The key of the node to look for.
 * @param[out] data   The data of the found node.
 */
btree_error btree_node_search(const btree_node *parent, const char *key, void **data);

#endif