#include "whc_p.h"

#include "list/list/list.h"
#include "list/node/node.h"
#include "../utils/utils.h"

#include "dirent.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/**
 * Initializes queue with given root path,
 * root path is copied to heap
 * @param root_path path to start directory
 * @return list of paths, used as a queue
 */
static list *init_queue(const char *root_path) {
    // Calculating length for dynamically allocated root path
    int len = strlen(root_path) + 1;

    // Allocating root path
    char *temp = (char *) malloc(len);

    // Copying
    strcpy(temp, root_path);

    // Finishing with \0
    temp[len - 1] = '\0';

    // Creating _queue
    list *queue = list_new();

    // Adding root path to _queue
    list_append(queue, node_new(temp, -1));

    // Returning _queue
    return queue;
}

/**
 * whereis implementation
 * (compatible with pthread)
 */
void *whs_p(void *args) {
    // Initializing result
    list *result = list_new();

    // Unpacking whs_p_args
    whs_p_args *a = (whs_p_args *)args;

    // Initializing queue
    list *queue = init_queue((char *)a->root);

    // Initializing target
    char *target = (char *)a->filename;

    // Searching directory graph in wide
    node *current = list_head(queue);
    DIR *temp;
    while(current != NULL) {
        // Searching in first queue directory
        temp = process_dir((char *)node_value(current), target,
                      &queue, &result);

        // Closing searched dir
        closedir(temp);

        // Moving to next member
        current = node_next(current);
    }

    // Deallocating
    list_free(queue, &free_dir_path);

    // Returning
    return (void *)result;
}
