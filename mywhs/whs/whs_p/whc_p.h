#ifndef MYWHS_DEMO_WHC_P_H
#define MYWHS_DEMO_WHC_P_H

/**
 * whs_p argument struct
 * @param root - path to start directory
 * @param filename - file name to search for
 */
typedef struct {
    char *root;
    char *filename;
} whs_p_args;

/**
 * Runs graph-wide search with given args
 * (compatible with pthread)
 * @param argv search arguments (whs_p_args instance)
 * @return list, contains search result (full paths to files with specified name)
 */
void *whs_p(void *argv);

#endif
