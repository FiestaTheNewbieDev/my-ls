#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <directory.h>

int main(int argc, char *argv[]) {
    char path;
    
    char **args = parse_flags(argv, &path);

    int file_count;
    char **files = list_files(path, false, false, &file_count);

    if (files == NULL) return EXIT_SUCCESS;

    for (int i = 0; i < file_count; i++) {
        printf("%s\n", files[i]);
    }

    return EXIT_SUCCESS;
}