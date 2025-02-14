#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "directory.h"
#include <stdio.h>
#include <sys/stat.h>

bool is_directory(char *path) {
    DIR *dir = opendir(path);
    if (dir != NULL) {
        closedir(dir);
        return true;
    }
    return false;
}

file* list_files(char *path, bool almost_all, bool all, int *count, int *total) {
    DIR *dir;
    struct dirent *entry;
    file* files = NULL;
    int file_count = 0;
    int total_size = 0;

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

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        files = realloc(files, sizeof(file) * (file_count + 1));
        if (files == NULL) {
            closedir(dir);
            return NULL;
        }

        files[file_count].name = strdup(entry->d_name);
        if (stat(full_path, &files[file_count].stat) == -1) {
            perror("stat");
            closedir(dir);
            free(files);
            return NULL;
        }

        printf("- %s: %ld\n", files[file_count].name, files[file_count].stat.st_blocks);
        total_size = files[file_count].stat.st_blocks;

        file_count++;
    }

    closedir(dir);
    *count = file_count;
    *total = total_size;
    return files;
}

file* list_files_recursive(char *path, bool almost_all, bool all, int *count, int *total) {
    DIR *dir;
    struct dirent *entry;
    file* files = NULL;
    int file_count = 0;
    int total_size = 0;

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

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        files = realloc(files, sizeof(file) * (file_count + 1));
        if (files == NULL) {
            closedir(dir);
            return NULL;
        }

        files[file_count].name = strdup(full_path);
        if (stat(full_path, &files[file_count].stat) == -1) {
            perror("stat");
            closedir(dir);
            free(files);
            return NULL;
        }

        files[file_count].files = NULL;
        files[file_count].file_count = 0;

        total_size += files[file_count].stat.st_blocks;

        if (S_ISDIR(files[file_count].stat.st_mode)) {
            int sub_count = 0;
            files[file_count].files = list_files_recursive(full_path, almost_all, all, &sub_count, &total_size);
            files[file_count].file_count = sub_count;
        }

        file_count++;
    }

    closedir(dir);
    *count = file_count;
    *total = total_size;
    return files;
}