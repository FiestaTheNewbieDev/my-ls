#include <directory.h>

#include "file.h"

#ifndef DISPLAY_H
#define DISPLAY_H

void simple_display(file* files, int file_count, bool recursive);
void detailed_display(file* files, int file_count, bool recursive);
int display_folder_name(file *folders, int folder_count);

#endif