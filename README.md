# Mini-libc
Use Make to build a minimalistic version of the standard C library (https://en.wikipedia.org/wiki/C_standard_library) implementation for Linux systems, that can be used as a replacement for the system libc ([glibc](https://www.gnu.org/software/libc/) in Linux).
The used code has minimally functional libc features such as string management, basic memory support and POSIX file I/O.

This implementation of mini-libc is freestanding, i.e. it does not use any outside library calls.

# Code

The code consists of the functions implemented in the src/ directory.
System call invocation is done via the `syscall()` function defined in `src/syscall.c`.
That itself makes a call to the architecture-specific call in `src/internal/arch/x86_64/syscall_arch.h`;


- `<string.h>`: defines string-handling functions

  The following functions are implemented: `strcpy()`, `strcat()`, `strlen()`, `strncpy()`, `strncat()`, `strcmp()`, `strncmp()`, `strstr()`, `strrstr()`, `memcpy()`, `memset()`, `memmove()`, `memcmp()`.

- `<stdio.h>`: defines printing and I/O functions

  The following function is implemented: `puts()`.

- `<unistd.h>`, `<sys/fcntl.h>` and `<sys/stat.h>`: define I/O primitives

  The following functions are implemented: `open()`, `close()`, `lseek()`, `stat()`, `fstat()`, `truncate()`, `ftruncate()`.

- `<stdlib.h`> and `<sys/mman.h>` define memory allocation functions

  The following functions are implemented: `malloc()`, `free()`, `calloc()`, `realloc()`, `realloc_array()`, `mmap()`, `mremap()`, `munmap()`.

  For managing memory areas, a basic list structure is found in `include/internal/mm/mem_list.h` and `mm/mem_list.c`.
  Also, `nanosleep()` and `sleep()` functions are in `src/process`.

- `<errno.h>` and `errno.c`: declare and define the integer variable `errno`, which is set by system calls and some library functions in the event of an error to indicate what went wrong.

# Building mini-libc

To build mini-libc, run `make` in the `src/` directory: