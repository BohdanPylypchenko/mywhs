#include "mywhs/whs/whs.h"

#include "list/list/list.h"
#include "list/node/node.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dirent.h>
#include <string.h>

// Filename to search
static char *filename = "mywhs_demo";

// Directory to start search in
static char *start_dir_path = "/";

// Short command line options
static char *short_options = "f:r:m";

// Long command line options
static struct option long_options[] = {{"filename", required_argument, 0, 'f'},
                                       {"start-directory", required_argument, 0, 'r'},
                                       {"multi-thread", no_argument, 0, 'm'}};

/**
 * Checks if optarg var is ""
 * @param option current command-line option to process (need to display if error)
 * @return non-zero if optarg is "", else zero
 */
static int empty_arg(int option);

/**
 * Checks if optarg var starts with '-'
 * @param option current command-line option to process (need to display if error)
 * @return non-zero if optarg starts with '-', else zero
 */
static int hyphen_arg(int option);

/**
 * File path (path represented as string in heap) deallocator
 * @param path pointer to heap string - path representation
 */
static void free_file_path(void *path);

/**
 * main
 */
int main(int argc, char *argv[]) {
    // Parsing command line arguments
    int mt_flag = 0;
    int current_option;
    int current_long_option_index = 0;
    while ((current_option = getopt_long(argc, argv,
                                         short_options, long_options,
                                         &current_long_option_index)) != -1) {
        switch (current_option) {
            case 'f':
                if (empty_arg(current_option)) return 1;
                if (hyphen_arg(current_option)) return 1;
                filename = optarg;
                break;
            case 'r':
                if (empty_arg(current_option)) return 1;
                if (hyphen_arg(current_option)) return 1;
                start_dir_path = optarg;
                break;
            case 'm':
                mt_flag = 1;
                break;
            case '?':
                printf("Usage: [-f | --filename] arg, [-r | --start-directory] arg, [-m | --multi-thread]\n");
                return 1;
            default:
                abort();
        }
    }

    // Checking if start_dir_path directory exists
    DIR *dir;
    if ((dir = opendir(start_dir_path)) == NULL) {
        // Start directory can't be open -> exit with error
        fprintf(stderr,
                "can't open start directory '%s'\n",
                start_dir_path);
        return 1;
    }
    else {
        // Start directory opened successfully -> close
        closedir(dir);
    }

    // Checking if start_dir_path ends with '/'
    int path_normalize_flag = 0;
    int start_dir_path_len = strlen(start_dir_path);
    if (start_dir_path[start_dir_path_len - 1] != '/') {
        // Path does not end with '/', need to add
        path_normalize_flag = 1;
        char *temp = (char *) malloc((start_dir_path_len + 2) * sizeof(char));
        strcpy(temp, start_dir_path);
        temp[start_dir_path_len] = '/';
        temp[start_dir_path_len + 1] = '\0';
        start_dir_path = temp;
    }

    // Searching
    list *result;
    if (mt_flag) {
        printf("running whs with params: file '%s' root-directory '%s' multi-thread",
               filename,
               start_dir_path);
        result = whs_mt(filename, start_dir_path);
    }
    else {
        printf("running whs with params: file '%s' root-directory '%s' one-thread",
               filename,
               start_dir_path);
        result = whs_1t(filename, start_dir_path);
    }

    // Printing
    printf("\nFound:\n");
    node *current = list_head(result);
    while (current != NULL) {
        printf("%s\n", (char *)node_value(current));
        current = node_next(current);
    }

    // Deallocating
    list_free(result, &free_file_path);
    if (path_normalize_flag) free_file_path(start_dir_path);

    // Returning
    return 0;
}

/**
 * empty_arg implementation
 */
static int empty_arg(int option) {
    if (optarg[0] == '\0') {
        fprintf(stderr,
                "empty-string arguments are not allowed for option '%c'\n",
                option);
        return 1;
    }
    else {
        return 0;
    }
}

/**
 * hyphen_arg implementation
 */
static int hyphen_arg(int option) {
    if (optarg[0] == '-') {
        fprintf(stderr,
                "hyphen-started arguments are not allowed for option '%c'\n",
                option);
        return 1;
    }
    else {
        return 0;
    }
}

/**
 * free_file_path implementation
 */
static void free_file_path(void *path) {
    free(path);
}
