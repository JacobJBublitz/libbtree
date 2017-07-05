#include "btree.h"

#include <stdlib.h>
#include <string.h>

btree_error btree_create(btree **tree, const char *key, void *data) {
    return btree_node_create(tree, key, data);
}

void btree_destroy(btree *tree) {
    return btree_node_destroy(tree);
}

void btree_foreach(const btree *tree, btree_foreach_proc_t foreach_proc) {
    btree_node_foreach(tree, foreach_proc);
}

btree_error btree_insert(btree *tree, const char *key, void *data) {
    btree_node *new_node;
    btree_error error = btree_node_create(&new_node, key, data);
    if (error != BTREE_ERROR_NONE) {
        return error;
    }

    error = btree_node_insert(tree, new_node);
    if (error != BTREE_ERROR_NONE) {
        return error;
    }
}

btree_error btree_remove(btree *tree, const char *key, void **data) {
    return btree_node_remove(tree, key, data);
}

btree_error btree_search(const btree *tree, const char *key, void **data) {
    return btree_node_search(tree, key, data);
}

btree_error btree_node_create(btree_node **node, const char *key, void *data) {
    *node = calloc(1, sizeof(btree_node));
    if (!(*node)) {
        return BTREE_ERROR_OUT_OF_MEMORY;
    }

    // Copy the key
    (*node)->key = calloc(strlen(key) + 1, sizeof(char));
    memcpy((*node)->key, key, strlen(key) * sizeof(char));

    // Set the data
    (*node)->data = data;

    return BTREE_ERROR_NONE;
}

void btree_node_destroy(btree_node *node) {
    if (node->left) {
        btree_node_destroy(node->left);
    }
    if (node->right) {
        btree_node_destroy(node->right);
    }

    free(node->key);
    free(node);
}

void btree_node_foreach(const btree_node *node, btree_foreach_proc_t foreach_proc) {
    if (node->left) {
        btree_node_foreach(node->left, foreach_proc);
    }
    if (node->right) {
        btree_node_foreach(node->right, foreach_proc);
    }

    foreach_proc(node->key, node->data);
}

btree_error btree_node_insert(btree_node *parent, btree_node *node) {
    int result = strcmp(parent->key, node->key);

    if (result > 0) {
        if (parent->right) {
            return btree_node_insert(parent->right, node);
        } else {
            parent->right = node;
            node->parent = parent;
            return BTREE_ERROR_NONE;
        }
    } else if (result < 0) {
        if (parent->left) {
            return btree_node_insert(parent->left, node);
        } else {
            parent->left = node;
            node->parent = parent;
            return BTREE_ERROR_NONE;
        }
    } else {
        return BTREE_ERROR_KEY_ALREADY_EXISTS;
    }
}

btree_error btree_node_remove(btree_node *node, const char *key, void **data) {
    int result = strcmp(node->key, key);

    if (result > 0) {
        if (node->right) {
            return btree_node_remove(node->right, key, data);
        } else {
            return BTREE_ERROR_KEY_NOT_FOUND;
        }
    } else if (result < 0) {
        if (node->left) {
            return btree_node_remove(node->left, key, data);
        } else {
            return BTREE_ERROR_KEY_NOT_FOUND;
        }
    } else {
        if (data) {
            *data = node->data;
        }

        if (node->left && node->right) {
            // Take the right node off the tree
            btree_node *right;
            {
                btree_error error = btree_node_create(&right, node->right->key, node->right->data);
                if (error != BTREE_ERROR_NONE) {
                    return error;
                }

                error = btree_node_insert(right, node->right->right);
                if (error != BTREE_ERROR_NONE) {
                    return error;
                }

                error = btree_node_insert(right, node->right->left);
                if (error != BTREE_ERROR_NONE) {
                    return error;
                }

                node->right = NULL;
            }

            // Move the left node to the parent node
            btree_node *old_left = node->left;
            free(node->key);
            node->key = old_left->key;
            node->data = old_left->data;
            node->left = old_left->left;
            node->right = old_left->right;

            // Destroy the old left node
            old_left->key = NULL;
            old_left->left = old_left->right = NULL;
            btree_node_destroy(old_left);

            // Insert the right node
            btree_node_insert(node, right);
        } else if (node->left || node->right) {
            btree_node *child;
            if (node->left) {
                child = node->left;
            } else {
                child = node->right;
            }

            node->right = child->right;
            node->left = child->left;
            node->data = child->data;

            char *old_key = node->key;
            node->key = child->key;

            child->key = old_key;
            child->left = child->right = NULL;
            btree_node_destroy(child);
        } else {
            if (node == node->parent->left) {
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }

            btree_node_destroy(node);
        }
    }

    return BTREE_ERROR_NONE;
}

btree_error btree_node_search(const btree_node *parent, const char *key, void **data) {
    int result = strcmp(parent->key, key);

    if (result > 0) {
        if (parent->right) {
            btree_node_search(parent->right, key, data);
        } else {
            return BTREE_ERROR_KEY_NOT_FOUND;
        }
    } else if (result < 0) {
        if (parent->left) {
            btree_node_search(parent->left, key, data);
        } else {
            return BTREE_ERROR_KEY_NOT_FOUND;
        }
    } else {
        *data = parent->data;
        return BTREE_ERROR_NONE;
    }
}
