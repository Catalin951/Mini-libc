// SPDX-License-Identifier: BSD-3-Clause

#include <internal/syscall.h>
#include <time.h>
unsigned int sleep(unsigned int seconds)
{
    struct timespec t1;
    t1.tv_sec = seconds;
    t1.tv_nsec = 0;
    struct timespec t2;
    t2.tv_sec = 0;
    t2.tv_nsec = 0;
    int result = nanosleep((const struct timespec*)&t1, &t2);
    if (result < 0) {
        return t2.tv_sec;
    }
    return result;
}

