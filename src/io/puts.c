// SPDX-License-Identifier: BSD-3-Clause

#include <internal/syscall.h>
#include <errno.h>

int puts(const char *str) {
    int len = 0;
    while (*str) {
        long result = syscall(1, 1, str, 1);
        if (result < 0)
            return -1;
        str++;
        len++;
    }
    const char null[2] = "\n";
    long result = syscall(1, 1, null, 1);
        if (result < 0)
            return -1;
    return len;
}
