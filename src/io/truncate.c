// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int truncate(const char *path, off_t length)
{
	if (!path)
		return -1;
	int flags = O_WRONLY;
	int fd = open(path, flags);
	if (fd == -1)
		return -1;
	long result = syscall(77, fd, length);
	if (result < 0) {
		errno = -result;
		return -1;
	}
	return 0;
}
