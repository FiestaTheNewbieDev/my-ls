#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "flags.h"
#include "arrays.h"
#include "display.h"
#include "directory.h"

#define INITIAL_PATH_SIZE 1

int main(int argc, char *argv[]) {
    char **path = malloc(INITIAL_PATH_SIZE * sizeof(char*));
    int path_count = 0;

    if (path == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    int flag_count;
    char **flags = get_flags(argc, argv, &path, &path_count, &flag_count);

    file* files = NULL;
    int file_count = 0;
    int total = 0;


    for (int i = 0; i < path_count; i++) {
        if (path_count > 1) {
            printf("%s : \n", path[i]);
        }

        if (includes(flags, flag_count, "-R") && path_count == 0) {
            files = list_files_recursive(path[i], includes(flags, flag_count, "-A"), includes(flags, flag_count, "-a"), &file_count, &total);
        } else {
            files = list_files(path[i], includes(flags, flag_count, "-A"), includes(flags, flag_count, "-a"), &file_count, &total);
        }

        if (files == NULL) {
            free(path);
            exit(EXIT_SUCCESS);
        }
    
        if (includes(flags, flag_count, "-l")) {
            detailed_display(files, file_count, total, path[i], includes(flags, flag_count, "-R") && path_count == 0);
        } else {
            simple_display(files, file_count, path[i], includes(flags, flag_count, "-R") && path_count == 0);
        }

        if (path_count > 1){
            printf("\n");
        }
    }



    return EXIT_SUCCESS;
}