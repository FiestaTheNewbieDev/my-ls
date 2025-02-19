#include <stdbool.h>
#include <sys/stat.h>

#ifndef DIRECTORY_H
#define DIRECTORY_H

typedef struct file {
    char* name;
    struct stat stat;
    struct file *files;
    int file_count;
} file;

bool is_directory(char *path);
file* list_files(char *path, bool almost_all, bool all, int *count, int *total);
file* list_files_recursive(char *path, bool almost_all, bool all, int *count, int *total);

#endif