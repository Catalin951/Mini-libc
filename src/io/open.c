// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	va_list args;
	mode_t mode = 0;
	// create new file if it doesnt exist
	// mode gives the permissions
	if(flags & O_CREAT) {
		va_start(args, flags);
		mode = va_arg(args, mode_t);
		va_end(args);
	}
	long result = syscall(2, filename, flags, mode);
	// if syscall failed
    if (result < 0) {
		// set errno variable
        errno = -result;
		// return error code
        return -1;
    }
	//return file descriptor
    return result;
}
