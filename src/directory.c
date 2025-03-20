#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
// #include <sys/stat.h>

#include "file.h"
#include "constants.h"
#include "directory.h"

bool is_directory(char *path) {
    DIR *dir = opendir(path);
    if (dir != NULL) {
        closedir(dir);
        return true;
    }
    return false;
}

bool is_nav_dir(char *path) {
    return strcmp(path, CURRENT_DIR) == 0 || strcmp(path, PARENT_DIR) == 0;
}

bool is_hidden(char *path) {
    return path[0] == '.';
}

bool is_already_listed(file *files, int file_count, const char *name) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, name) == 0) {
            return true;
        }
    }
    return false;
}

void list_files(file *folders, int folder_count, bool almost_all, bool all, bool recursive) {
    for (int i = 0; i < folder_count; i++) {
        DIR *dir;
        struct dirent *entry;

        file **files = &folders[i].files;
        int *file_count = &folders[i].file_count;

        if (!is_directory(folders[i].path)) return;

        dir = opendir(folders[i].path);
        if (dir == NULL) return;

        while ((entry = readdir(dir)) != NULL) {
            if (!all) {
                if (almost_all) {
                    if (is_nav_dir(entry->d_name)) continue;
                } else {
                    if (is_hidden(entry->d_name)) continue;
                }
            }

            if (is_already_listed(*files, *file_count, entry->d_name)) {
                continue;
            }

            char full_path[PATH_MAX];
            snprintf(full_path, sizeof(full_path), "%s/%s", folders[i].path, entry->d_name);

            file *tmp_files = realloc(*files, sizeof(file) * (*file_count + 1));
            if (tmp_files == NULL) {
                perror("realloc");
                free_files(*files, *file_count);
                closedir(dir);
                return;
            }
            *files = tmp_files;

            (*files)[*file_count] = create_file(entry->d_name, full_path);
            if (stat(full_path, &(*files)[*file_count].stat) == -1) {
                perror("stat");
                free_files(*files, *file_count);
                closedir(dir);
                return;
            }

            folders[i].total += (*files)[*file_count].stat.st_blocks / 2;
            (*file_count)++;

            if (recursive && is_directory((*files)[*file_count - 1].path) && !is_nav_dir(entry->d_name)) {
                list_files(&(*files)[*file_count - 1], 1, almost_all, all, recursive);
            }
        }

        closedir(dir);
    }
}
