#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <directory.h>
#include <string.h>
#include "flags.h"

#define INITIAL_PATH_SIZE 1

int main(int argc, char *argv[]) {
    // Init path and allocate memory
    char *path = malloc(INITIAL_PATH_SIZE * sizeof(char));
    if (path == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    strcpy(path, ".");

    int flag_count;
    char **flags = get_flags(argc, argv, &path, &flag_count);

    int file_count;
    char **files = list_files(path, false, false, &file_count);

    if (files == NULL) {
        free(path);
        return EXIT_SUCCESS;
    }

    for (int i = 0; i < file_count; i++) {
        printf("%s\n", files[i]);
    }

    for (int i = 0; i < flag_count; i++) {
        printf("%s\n", flags[i]);
    }

    return EXIT_SUCCESS;
}