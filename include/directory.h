#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <stdbool.h>
#include <sys/stat.h>

typedef struct {
    char* name;
    struct stat stat;
} file_info;

bool is_directory(char *path);
file_info* list_files(char *path, bool almost_all, bool all, int *count);

#endif