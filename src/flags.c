#include <stddef.h>
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

#include "flags.h"
#include "directory.h"
#include "arrays.h"

char** get_flags(int argc, char *argv[], char ***path, int *path_count, int *count) {
    char **flags = NULL;
    int flag_count = 0;

    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            flags = realloc(flags, (flag_count + 1) * sizeof(char*));
            flags[flag_count] = argv[i];
            flag_count++;
        } else { 
            if (is_directory(argv[i])) {
                size_t len = strlen(argv[i]) + 1;
                char *new_path = malloc(len * sizeof(char));
                if (new_path == NULL) {
                    perror("malloc");
                    free(flags);
                    exit(EXIT_FAILURE);
                }
                strncpy(new_path, argv[i], len);

                *path = realloc(*path, (*path_count + 1) * sizeof(char*));
                if (*path == NULL) {
                    perror("realloc");
                    free(new_path);
                    free(flags);
                    exit(EXIT_FAILURE);
                }

                (*path)[*path_count] = new_path;
                (*path_count)++;
            }
        }
    }

    if (len(*path) == 0) {
        *path = malloc(1 * sizeof(char*));
        (*path)[0] = ".";
        (*path_count)++;
    }
    *count = flag_count;
    return flags;
}
