#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>

#include "file.h"
#include "directory.h"
#include "display.h"

void simple_display(file *folders, int folder_count, bool recursive) {
    for (int i = 0; i < folder_count; i++) {
        if (folder_count > 1) {
            printf("%s:\n", folders[i].path);
        }

        file *files = folders[i].files;
        int file_count = folders[i].file_count;

        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int terminal_width = w.ws_col;

        int max_file_length = 0;
        for (int i = 0; i < file_count; i++) {
            if (files[i].name == NULL) exit(EXIT_FAILURE);

            int len = strlen(files[i].name);
            if (len > max_file_length) {
                max_file_length = len;
            }
        }

        int columns = terminal_width / (max_file_length + 1);
        if (columns == 0) columns = 1;

        for (int i = 0; i < file_count; i++) {
            printf("%-*s", max_file_length + 1, files[i].name);
            if ((i + 1) % columns == 0) {
                printf("\n");
            }
        }
        if (file_count % columns != 0) {
            printf("\n");
        }

        for (int i = 0; i < file_count; i++) {
            if (recursive && files[i].files) {
                printf("\n");
                simple_display(files[i].files, files[i].file_count, file_count > 0);
            }
        }
    }
}

void print_permissions(mode_t mode) {
    char permissions[11];
    permissions[0] = (S_ISDIR(mode)) ? 'd' : '-';
    permissions[1] = (mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (mode & S_IXOTH) ? 'x' : '-';
    permissions[10] = '\0';
    printf("%s ", permissions);
}

void detailed_display(file* files, int file_count, int total, char *path, bool recursive) {
    if (recursive) {
        printf("%s:\n", path);
    }
    printf("total %d\n", total);

    for (int i = 0; i < file_count; i++) {
        print_permissions(files[i].stat.st_mode);
        printf("%ld ", (long)files[i].stat.st_nlink);

        struct passwd *pw = getpwuid(files[i].stat.st_uid);
        struct group *gr = getgrgid(files[i].stat.st_gid);
        printf("%s %s ", pw->pw_name, gr->gr_name);

        printf("%5ld ", (long)files[i].stat.st_size);

        char timebuf[80];
        struct tm *tm_info = localtime(&files[i].stat.st_mtime);
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);
        printf("%s ", timebuf);

        printf("%s\n", files[i].name);
    }

    for (int i = 0; i < file_count; i++) {
        if (recursive && is_directory(files[i].path)) {
            printf("\n");
            detailed_display(files[i].files, files[i].file_count, files[i].total, files[i].path, files[i].file_count > 0);
        }
    }
}