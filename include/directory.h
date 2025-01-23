#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <stdbool.h>

bool is_directory(char *path);
char** list_files(char *path, bool almost_all, bool all, int *count);

#endif