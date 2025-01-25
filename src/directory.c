#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "directory.h"
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>

bool is_directory(char *path) {
    DIR *dir = opendir(path);
    if (dir != NULL) {
        closedir(dir);
        return true;
    }
    return false;
}

file_info* list_files(char *path, bool almost_all, bool all, int *count) {
    DIR *dir;
    struct dirent *entry;
    file_info* files = NULL;
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
        
        files = realloc(files, sizeof(file_info) * (file_count + 1));
        if (files == NULL) {
            closedir(dir);
            return NULL;
        }

        files[file_count].name = strdup(entry->d_name);
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &files[file_count].stat) == -1) {
            perror("stat");
            closedir(dir);
            free(files);
            return NULL;
        }

        file_count++;
    }

    closedir(dir);
    *count = file_count;
    return files;
}