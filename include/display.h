#include <directory.h>

#ifndef DISPLAY_H
#define DISPLAY_H

void simple_display(file* files, int file_count, char *path, bool recursive);
void detailed_display(file* files, int file_count, int total, char *path, bool recursive);

#endif