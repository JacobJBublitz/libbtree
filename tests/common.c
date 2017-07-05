#include "common.h"

#include <stdio.h>
#include <stdlib.h>

void handle_error2(btree_error error, int line) {
    const char *error_name;

    switch (error) {
        case BTREE_ERROR_NONE:
            return;
        case BTREE_ERROR_KEY_NOT_FOUND:
            error_name = "BTREE_ERROR_KEY_NOT_FOUND";
            break;
        case BTREE_ERROR_KEY_ALREADY_EXISTS:
            error_name = "BTREE_ERROR_KEY_ALREADY_EXISTS";
            break;
        case BTREE_ERROR_OUT_OF_MEMORY:
            error_name = "BTREE_ERROR_OUT_OF_MEMORY";
            break;
        default:
            error_name = "UNKNOWN";
            break;
    }

    fprintf(stderr, "libbtree failed with error '%s'. (Line %d)\n", error_name, line);

    exit(EXIT_FAILURE);
}

void handle_failure(const char *funcname) {
    fprintf(stderr, "libbtree failed on '%s'.\n", funcname);
    exit(EXIT_FAILURE);
}