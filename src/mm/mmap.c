// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>
#include <unistd.h>
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	struct stat st;
	// not map_anonymous
	if(!(flags & MAP_ANONYMOUS)) {
		// fd must not be -1
		if(fd == -1) {
			errno = EBADF;
			return MAP_FAILED;
		}
		// check if fd is valid
		// fstat modifies errno
		fstat(fd, &st);
		if (errno == EBADF)
			return MAP_FAILED;
	}
	// check if mapping is anonymous and
	// none of private and shared flags are on
	if((flags & MAP_ANONYMOUS) && !(flags & MAP_PRIVATE) && !(flags & MAP_SHARED)) {
		errno = EINVAL;
		return MAP_FAILED;
	}

	long result = syscall(9, addr, length, prot, flags, fd, offset);
	// pointer to memory
	return (void *) result;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	if (!old_address) {
		errno = EINVAL;
		return MAP_FAILED;
	}
	void *result = (void *) syscall(25, old_address, old_size, new_size, flags);
	if (result == MAP_FAILED)
		return result;
	return result;
}

int munmap(void *addr, size_t length)
{
	long result = syscall(11, addr, length);
	if (result < 0) {
		// syscall failed, set errno
		errno = -result;
		return -1;
	}
	return result;
}
