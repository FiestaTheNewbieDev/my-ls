#include "arrays.h"
#include <stdbool.h>
#include <string.h>

bool includes(char *arr[], int len, char *str) {
    for (int i = 0; i < len; i++) {
        if (strcmp(arr[i], str) == 0) {
            return true;
        }
    }
    return false;
}
