#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include "directory.h"
#include "display.h"

void simple_display(char **files, int file_count) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int terminal_width = w.ws_col;

    int max_file_length = 0;
    for (int i = 0; i < file_count; i++) {
        int len = strlen(files[i]);
        if (len > max_file_length) {
            max_file_length = len;
        }
    }

    int columns = terminal_width / (max_file_length + 1);
    if (columns == 0) columns = 1;

    for (int i = 0; i < file_count; i++) {
        printf("%-*s", max_file_length + 1, files[i]);
        if ((i + 1) % columns == 0) {
            printf("\n");
        }
    }
    if (file_count % columns != 0) {
        printf("\n");
    }
}