#include "utils.h"

#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*
 * Dotty members
 */
static const char *DOT = ".";
static const char *DOTDOT = "..";

/**
 * dotty check implementation
 */
int dotty_check(const char *name) {
    if (strcmp(name, DOT) == 0 ||
        strcmp(name, DOTDOT) == 0) {
        return 1;
    }
    return 0;
}

/**
 * DIR pointer getter implementation
 */
DIR *get_dir_ptr(const char *path) {
    // Opening directory
    DIR *dir = opendir(path);

    // Failure check
    if (dir == NULL) {
        fprintf(stderr, "Error: can't open directory:\n%s\n", path);
    }

    // No failure -> return dir ptr
    return dir;
}

/**
 * Absolute path getter implementation
 */
char *get_absolute_path(const char *dir_path,
                        const char *name, const short slash_flag) {
    // Calculating length
    int len = strlen(dir_path) + strlen(name) + slash_flag + 1;

    // Allocating memory
    char *absolute_path = (char *)calloc(len, 1);

    // Concatenating
    strcat(absolute_path, dir_path);
    strcat(absolute_path, name);

    // Checking for need to add /
    if (slash_flag == 1) {
        // Adding /
        absolute_path[len - 2] = '/';
    }

    // Finishing with \0
    absolute_path[len - 1] = '\0';

    // Returning
    return absolute_path;
}

/**
 * process_dir implementation
 */
DIR *process_dir(const char *dir_path, const char *target,
                 const list **queue, const list **result) {
    // Getting dir ptr
    DIR *dir = get_dir_ptr(dir_path);

    // Checking for error
    if (dir == NULL) {
        // Could not open dir -> skip
        closedir(dir);
        return NULL;
    }

    // Iterating though dir members
    struct dirent *member;
    char *absolute_path;
    while ((member = readdir (dir)) != NULL) {
        // Checking for dotty members
        if (dotty_check(member->d_name) == 1) {
            // Move to next member
            continue;
        }

        // Is member a directory?
        if (member->d_type == UNIX_DIRECTORY) {
            // Add absolute path of new directory to queue
            absolute_path = get_absolute_path(dir_path, member->d_name, 1);
            list_append(*queue, node_new(absolute_path, -1));

            // Move to next member
            continue;
        }

        // Is member a file with searched name?
        if (member->d_type == UNIX_FILE && strcmp(target, member->d_name) == 0) {
            // Add member absolute path to result
            absolute_path = get_absolute_path(dir_path, member->d_name, 0);
            list_append(*result, node_new(absolute_path, -1));

            // Stop searching
            break;
        }
    }

    // Returning dir
    return dir;
}

/**
 * free_dir_path implementation
 */
void free_dir_path(void *path) {
    free(path);
}
