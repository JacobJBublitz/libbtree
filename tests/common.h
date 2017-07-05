#ifndef LIBBTREE_TEST_COMMON_H
#define LIBBTREE_TEST_COMMON_H

#include <btree.h>

void handle_failure(const char *function);

#define handle_error(error) handle_error2(error, __LINE__)
void handle_error2(btree_error error, int line);

#endif