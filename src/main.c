#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "flags.h"
#include "arrays.h"
#include "display.h"
#include "directory.h"

#define INITIAL_PATH_SIZE 1

void recursive(char *path, char **flags, int flag_count) {
    int file_count;
    file* files = list_files(path, includes(flags, flag_count, "-A"), includes(flags, flag_count, "-a"), &file_count);

    if (files == NULL) {
        free(path);
        exit(EXIT_SUCCESS);
    }

    printf("%s:\n", path);
    if (includes(flags, flag_count, "-l")) {
        detailed_display(files, file_count);
    } else {
        simple_display(files, file_count);
    }
    printf("\n");
}

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

    if (includes(flags, flag_count, "-R")) files = list_files_recursive(path, includes(flags, flag_count, "-A"), includes(flags, flag_count, "-a"), &file_count);
    else files = list_files(path, includes(flags, flag_count, "-A"), includes(flags, flag_count, "-a"), &file_count);

    if (files == NULL) {
        free(path);
        exit(EXIT_SUCCESS);
    }

    if (includes(flags, flag_count, "-l")) {
        detailed_display(files, file_count);
    } else {
        simple_display(files, file_count);
    }

    return EXIT_SUCCESS;
}