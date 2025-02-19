#include <stdbool.h>
#include <sys/stat.h>

#ifndef DIRECTORY_H
#define DIRECTORY_H

typedef struct file {
    char *name;
    char *path;
    struct stat stat;
    struct file *files;
    int file_count;
    int total;
} file;

bool is_directory(char *path);
file* list_files(char *path, bool almost_all, bool all, int *count, int *total);
file* list_files_recursive(char *path, bool almost_all, bool all, int *count, int *total);

#endif