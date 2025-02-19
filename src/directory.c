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

void list_files(file *folders, int folder_count, bool almost_all, bool all, bool recursive) {
    if (recursive) return;

    for (int i = 0; i < folder_count; i++) {
        printf("%s\n", folders[i].path);

        DIR *dir;
        struct dirent *entry;

        file **files =  &folders[i].files;
        int *file_count = &folders[i].file_count;

        if (!is_directory(folders[i].path)) return;

        dir = opendir(folders[i].path);
        if (dir == NULL) return;

        while ((entry = readdir(dir)) != NULL) {
            if (!all) {
                if (almost_all) {
                    if (strcmp(entry->d_name, CURRENT_DIR) == 0 || strcmp(entry->d_name, PARENT_DIR) == 0) continue;
                } else {
                    if (entry->d_name[0] == '.') continue;
                }
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
        }

        closedir(dir);
    }
}