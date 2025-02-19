#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "flags.h"
#include "arrays.h"
#include "display.h"
#include "directory.h"

#define INITIAL_PATH_SIZE 1

int main(int argc, char *argv[]) {
    char *path = malloc(INITIAL_PATH_SIZE * sizeof(char));
    if (path == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    strcpy(path, ".");

    int flag_count;
    char **flags = get_flags(argc, argv, &path, &flag_count);

    file* files = NULL;
    int file_count = 0;
    int total = 0;

    if (includes(flags, flag_count, "-R")) files = list_files_recursive(path, includes(flags, flag_count, "-A"), includes(flags, flag_count, "-a"), &file_count, &total);
    else files = list_files(path, includes(flags, flag_count, "-A"), includes(flags, flag_count, "-a"), &file_count, &total);

    if (files == NULL) {
        free(path);
        exit(EXIT_SUCCESS);
    }

    if (includes(flags, flag_count, "-l")) {
        detailed_display(files, file_count, total, path, includes(flags, flag_count, "-R"));
    } else {
        simple_display(files, file_count, path, includes(flags, flag_count, "-R"));
    }

    return EXIT_SUCCESS;
}