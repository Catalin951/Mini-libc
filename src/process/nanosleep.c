// SPDX-License-Identifier: BSD-3-Clause

#include <internal/syscall.h>
#include <errno.h>
#include <time.h>
int nanosleep(const struct timespec *t1, struct timespec *t2)
{
    long result = syscall(35, t1, t2);
    if (result < 0) {
        errno = -result;
        return -1;
    }
    return result;
}

