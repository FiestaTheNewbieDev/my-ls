#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "flags.h"
#include "arrays.h"
#include "display.h"
#include "directory.h"

#define INITIAL_PATH_SIZE 1

int main(int argc, char *argv[]) {
    file *folders = NULL;
    int folder_count = 0;

    int flag_count = 0;
    char **flags = get_flags(argc, argv, &folders, &folder_count, &flag_count);

    bool recursive = includes(flags, flag_count, "-R") && folder_count <= 1;

    list_files(folders, folder_count, includes(flags, flag_count, "-A"), includes(flags, flag_count, "-a"), recursive);

    if (folders == NULL) {
        free_files(folders, folder_count);
        free(flags);
        return EXIT_SUCCESS;
    }

    if (includes(flags, flag_count, "-l")) {
        detailed_display(folders, folder_count, recursive);
    } else simple_display(folders, folder_count, recursive);

    return EXIT_SUCCESS;
}