// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st)
{
	long result = syscall(5, fd, st);
	if(result < 0) {
		errno = -result;
		return -1;
	}
	return result;
}
