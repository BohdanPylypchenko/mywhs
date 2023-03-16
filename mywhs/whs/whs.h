#ifndef MYWHS_DEMO_WHS_H
#define MYWHS_DEMO_WHS_H

#include "list/list/list.h"

/**
 * Searches for file with given name in directory tree, starting from given
 * (one-threaded)
 * @param filename name of file to search for
 * @param root_dir_path path to directory to start search in
 * @return list of paths to all occurrences of files with given name
 */
list *whs_1t(const char *filename,
             const char *root_dir_path);

/**
 * Searches for file with given name in directory tree, starting from given
 * (multi-threaded)
 * @param filename name of file to search for
 * @param root_dir_path path to directory to start search in
 * @return list of paths to all occurrences of files with given name
 */
list *whs_mt(const char *filename,
             const char *root_dir_path);

#endif
