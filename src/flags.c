#include "flags.h"
#include "directory.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char **get_flags(int argc, char *argv[], char *path) {
    char **flags = NULL;
    int flag_count = 0;

    for (int i = 0; i < argc; i++){
        if (argv[i][0] == '-') {
            flags = realloc(flags, (flag_count + 1) * sizeof(char*));
            flags[i] = argv[i];
        } else { 
            if (is_directory(argv[i])) { 
                strncpy(path, argv[i], 255);
                path[255] = '\0';
            }
        }
    }

    return flags;

}