#ifndef MYWHS_DEMO_UTILS_H
#define MYWHS_DEMO_UTILS_H

#include "list/list/list.h"

#include <dirent.h>
#include <pthread.h>

// Member types
#define UNIX_FILE 8
#define UNIX_DIRECTORY 4

/**
 * Checks if given name is dotty (is name equals to "." or ".."?)
 * @param name string to check
 * @return non-zero if dotty, else - zero
 */
int dotty_check(const char *name);

/**
 * Creates DIR pointer for given directory
 * (represented by its path)
 * @param path string, represents path of directory to open
 * @return pointer to opened dir, else - NULL
 */
DIR *get_dir_ptr(const char *path);

/**
 * Creates absolute path for member
 * example:
 * dir_path = "/dir1/dir2"
 * name = "the_file"
 * slash_flag = 1
 * result: "/dir1/dir2/the_file"
 * @param dir_path directory path to member
 * @param name member name
 * @param slash_flag indicates, if '/' char insertion
 *        between dir_path and name needed
 *        pass 1 to insert, otherwise - no insertion will be performed
 */
char *get_absolute_path(const char *dir_path,
                        const char *name, const short slash_flag);

/**
 * Process dir function
 * Adds inner directories to queue,
 * adds paths of occurrences with target name to result.
 * Returns pointer to processed dir
 * @param dir_path dir to process, represented with its path
 * @param target filename to search for
 * @param queue directory list (queue) to add all inner directories,
 *        thus inner directories would be processed in future
 * @param result string list to add founded members to
 * @return pointer to processed dir
 */
DIR *process_dir(const char *dir_path, const char *target,
                 const list **queue, const list **result);

/**
 * Deallocates given path (as string)
 * @param path string to free
 */
void free_dir_path(void *path);

#endif
