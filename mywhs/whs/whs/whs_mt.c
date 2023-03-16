#include "whs/whs.h"

#include "whs/utils/utils.h"
#include "whs/whs_p/whc_p.h"

#include <stddef.h>
#include "dirent.h"
#include <malloc.h>

/*
 * To free paths 2-dimensional list
 */
static void free_list_ptr(void *v) {
    free(v);
}

/**
 * whs_mt implementation
 */
list *whs_mt(const char *filename,
             const char *root_dir_path) {
    // Needed variables
    list *result;
    list *paths = list_new();
    list *directories = list_new();

    // Getting root info
    list *search_root_result = list_new();
    DIR *root = process_dir(root_dir_path, filename,
                            &directories, &search_root_result);
    int dir_count = list_len(directories);

    // Appending search root result to paths
    list_append(paths, node_new(search_root_result, -1));

    // Multithreading
    pthread_t *threads = (pthread_t *)malloc(dir_count * sizeof(pthread_t));
    whs_p_args *a = (whs_p_args *) malloc(dir_count * sizeof(whs_p_args));
    node *temp_node = list_head(directories);
    list *temp_l;
    for (int i = 0; i < dir_count; i++) {
        a[i].root = (char *) node_value(temp_node);
        a[i].filename = filename;
        pthread_create(&threads[i], NULL, &whs_p, (void *)&a[i]);
        temp_node = node_next(temp_node);
    }
    for (int i = 0; i < dir_count; i++) {
        pthread_join(threads[i], (void *)&temp_l);
        list_append(paths, node_new(temp_l, -1));
    }

    // Joining
    result = list_join(paths);

    // Deallocating
    closedir(root);
    list_free(paths, free_list_ptr);
    list_free(directories, free_dir_path);
    free(threads);
    free(a);

    // Returning
    return result;
}
