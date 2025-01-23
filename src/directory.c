#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "directory.h"
#include <stdio.h>

bool is_directory(char *path) {
    DIR *dir = opendir(path);
    if (dir != NULL) {
        closedir(dir);
        return true;
    }
    return false;
}

char** list_files(char *path, bool almost_all, bool all, int *count) {
    DIR *dir;
    struct dirent *entry;
    char **files = NULL;
    int file_count = 0;

    if (!is_directory(path)) return NULL;

    dir = opendir(path);
    if (dir == NULL) return NULL;

    while ((entry = readdir(dir)) != NULL) {
        if (!all) {
            if (almost_all) {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
            } else {
                if (entry->d_name[0] == '.') continue;
            }
        }
        
        files = realloc(files, sizeof(char*) * (file_count + 1));
        if (files == NULL) {
            closedir(dir);
            return NULL;
        }
        files[file_count] = strdup(entry->d_name);
        file_count++;
    }

    closedir(dir);
    *count = file_count;
    return files;
}