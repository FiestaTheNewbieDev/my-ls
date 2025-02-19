#include <stdbool.h>
#include <sys/stat.h>

#include "file.h"

#ifndef DIRECTORY_H
#define DIRECTORY_H

bool is_directory(char *path);

void list_files(file *folders, int folder_count, bool almost_all, bool all, bool recursive);

#endif