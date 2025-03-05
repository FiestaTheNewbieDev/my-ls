#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

file create_file(char *name, char *path) {
    file new_file;

    if (name == NULL || path == NULL) {
        fprintf(stderr, "Error: NULL string passed to create_file.\n");
        exit(EXIT_FAILURE);
    }

    new_file.name = strdup(name);
    if (new_file.name == NULL) {
        perror("strdup for name");
        exit(EXIT_FAILURE);
    }

    new_file.path = strdup(path);
    if (new_file.path == NULL) {
        perror("strdup for path");
        free(new_file.name);
        exit(EXIT_FAILURE);
    }

    // new_file.stat = NULL;

    new_file.files = NULL;
    new_file.file_count = 0;
    new_file.total = 0;

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

char* file_to_string(file file) {
    size_t size = snprintf(NULL, 0, "{\n  \"name\": \"%s\",\n  \"path\": \"%s\"\n}\n", file.name, file.path);
    
    char* result = malloc(size + 1);
    if (!result) return NULL;
    
    snprintf(result, size + 1, "{\n  \"name\": \"%s\",\n  \"path\": \"%s\"\n}\n", file.name, file.path);
    
    return result;
}
