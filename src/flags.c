#include <stddef.h>
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "flags.h"
#include "directory.h"
#include "arrays.h"

void add_flag(char ***flags, int *flag_count, char *flag) {
    char **tmp_flags = realloc(*flags, (*flag_count + 1) * sizeof(char*));
    if (tmp_flags == NULL) {
        perror("realloc");
        free(*flags);
        exit(EXIT_FAILURE);
    }
    *flags = tmp_flags;
    (*flags)[*flag_count] = flag;
    (*flag_count)++;
}

void add_folder(file **folders, int *folder_count, char *folder) {
    file *tmp_folders = realloc(*folders, (*folder_count + 1) * sizeof(file));
    if (tmp_folders == NULL) {
        perror("realloc");
        free_files(*folders, *folder_count);
        exit(EXIT_FAILURE);
    }
    *folders = tmp_folders;

    (*folders)[*folder_count] = create_file(folder, folder);
    (*folder_count)++;
}

char** get_flags(int argc, char *argv[], file **folders, int *folder_count, int *flag_count) {
    char **flags = NULL;

    for (int i = 1; i < argc; i++) {
        if (argv[i] == NULL || argv[i][0] == '\0') continue;

        if (argv[i][0] == '-') add_flag(&flags, flag_count, argv[i]);
        else if (is_directory(argv[i])) add_folder(folders, folder_count, argv[i]);
        else {
            fprintf(stderr, "%s: cannot access '%s': No such file or directory\n", APP_NAME, argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    if (*folder_count == 0) add_folder(folders, folder_count, ".");

    return flags;
}
