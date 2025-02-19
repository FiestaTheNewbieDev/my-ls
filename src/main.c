#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "flags.h"
#include "arrays.h"
#include "display.h"
#include "directory.h"

#define INITIAL_PATH_SIZE 1

// int main(int argc, char *argv[]) {
//     char **path = malloc(INITIAL_PATH_SIZE * sizeof(char*));
//     int path_count = 0;

//     if (path == NULL) {
//         perror("malloc");
//         return EXIT_FAILURE;
//     }

//     int flag_count;
//     char **flags = get_flags(argc, argv, &path, &path_count, &flag_count);

//     file* files = NULL;
//     int file_count = 0;
//     int total = 0;

//     bool recursive = includes(flags, flag_count, "-R") && path_count == 0;

//     for (int i = 0; i < path_count; i++) {
//         if (path_count > 1) {
//             printf("%s : \n", path[i]);
//         }

//         if (recursive) {
//             files = list_files_recursive(path[i], includes(flags, flag_count, "-A"), includes(flags, flag_count, "-a"), &file_count, &total);
//         } else {
//             files = list_files(path[i], includes(flags, flag_count, "-A"), includes(flags, flag_count, "-a"), &file_count, &total);
//         }

//         if (files == NULL) {
//             free(path);
//             exit(EXIT_SUCCESS);
//         }

//         if (includes(flags, flag_count, "-l")) {
//             detailed_display(files, file_count, total, path[i], recursive);
//         } else {
//             simple_display(files, file_count, path[i], recursive);
//         }

//         if (path_count > 1){
//             printf("\n");
//         }
//     }

//     return EXIT_SUCCESS;
// }

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
        printf("detailed display\n");
        return EXIT_SUCCESS;
    } else simple_display(folders, folder_count, recursive);

    return EXIT_SUCCESS;
}