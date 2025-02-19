#include "directory.h"

#include "file.h"

#ifndef FLAGS_H
#define FLAGS_H

char** get_flags(int argc, char *argv[], file **folders, int *folder_count, int *flag_count);

#endif