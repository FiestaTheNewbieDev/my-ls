#include "flags.h"
#include "directory.h"
#include <stddef.h>
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

char **get_flags(int argc, char *argv[], char **path, int *count) {
    char **flags = NULL;
    int flag_count = 0;

    for (int i = 0; i < argc; i++){
        if (argv[i][0] == '-') {
            flags = realloc(flags, (flag_count + 1) * sizeof(char*));
            flags[flag_count] = argv[i];
            flag_count++;
        } else { 
            if (is_directory(argv[i])) {
                size_t len = strlen(argv[i]) + 1;
                char *new_path = realloc(*path, len * sizeof(char));
                if (new_path == NULL) {
                    perror("realloc");
                    free(flags);
                    exit(EXIT_FAILURE);
                }
                *path = new_path;
                strncpy(*path, argv[i], len);
            }
        }
    }

    *count = flag_count;
    return flags;

}