// SPDX-License-Identifier: BSD-3-Clause

#include <internal/syscall.h>
#include <errno.h>

int puts(char *str) {
    while(*str) {
        long result = write(1, str, 1);
        if(result < 0)
            return -1;
        str++;
    }
    return 0;
}