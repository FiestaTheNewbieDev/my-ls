#include <directory.h>

#include "file.h"

#ifndef DISPLAY_H
#define DISPLAY_H

void simple_display(file* files, int file_count, bool recursive);
void detailed_display(file* files, int file_count, bool recursive);
int compare_modification_time(const void *a, const void*b);
void sort_folders_by_modification_time(file *folders, int folder_count, bool recursive);
#endif