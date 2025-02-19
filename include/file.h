#include <sys/stat.h>

#ifndef FILE_H
#define FILE_H

typedef struct file {
    char *name;
    char *path;
    struct stat stat;
    struct file *files;
    int file_count;
    int total;
} file;

file create_file(char *name, char *path);

void free_file(file *file);
void free_files(file *files, int file_count);

#endif