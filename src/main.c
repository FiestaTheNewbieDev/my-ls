#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <directory.h>
#include "flags.h"

int main(int argc, char *argv[]) {
    char path[256] = ".";

    char **args = get_flags(argc, argv, path);

    int file_count;
    char **files = list_files(path, false, false, &file_count);

    if (files == NULL) return EXIT_SUCCESS;

    for (int i = 0; i < file_count; i++) {
        printf("%s\n", files[i]);
    }

    return EXIT_SUCCESS;
}