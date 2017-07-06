add_library(common STATIC common.c common.h)
target_link_libraries(common PUBLIC libbtree)

add_executable(creation creation.c)
target_link_libraries(creation PRIVATE common)

add_executable(foreach foreach.c)
target_link_libraries(foreach PRIVATE common)

add_executable(remove remove.c)
target_link_libraries(remove PRIVATE common)

add_executable(root_remove root_remove.c)
target_link_libraries(root_remove PRIVATE common)