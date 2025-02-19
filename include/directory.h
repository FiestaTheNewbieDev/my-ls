#include <stdbool.h>
#include <sys/stat.h>

#include "file.h"

#ifndef DIRECTORY_H
#define DIRECTORY_H

bool is_directory(char *path);

file* list_files(char *path, bool almost_all, bool all, int *count, int *total);
file* list_files_recursive(char *path, bool almost_all, bool all, int *count, int *total);

#endif