#include <stdlib.h>

#include "file.h"

file create_file(char *name, char *path) {
    file new_file;
    new_file.name = name;
    new_file.path = path;
    // new_file.stat = NULL;
    // new_file.files = NULL;
    // new_file.file_count = 0;
    // new_file.total = 0;

    return new_file;
}

void free_file(file *file) {
    if (file == NULL) return;

    if (file -> name) free(file -> name);
    if (file -> path) free(file -> path);

    for (int i = 0; i < file -> file_count; i++) {
        free_file(&file -> files[i]);
    }

    free(file -> files);
}

void free_files(file *files, int file_count) {
    if (files == NULL) return;

    for (int i = 0; i < file_count; i++) {
        free_file(&files[i]);
    }

    free(files);
}