// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	void *start = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	// allocation failed
	if (start == MAP_FAILED)
		return NULL;
	mem_list_add(start, size);
	return start;
}

void *calloc(size_t nmemb, size_t size)
{
	if (!mem_list_head.start)
		mem_list_init();
	void *start = mmap(NULL, size * nmemb, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	// allocation failed
	if (start == MAP_FAILED)
		return NULL;
	void *iter = start;
	int i = 0;
	int len = size * nmemb;
	while (i < len) {
		*(char *) iter = 0;
		i++;
	}
	mem_list_add(start, size * nmemb);
	return start;
}

void free(void *ptr)
{
	if (!ptr)
		return;
	// need len of the memory map
	// also remove the element from list
	struct mem_list *mem_element = mem_list_find(ptr);

	// ptr is not valid
	if (!mem_element)
		return;
	// unmap memory at ptr
	munmap(mem_element->start, mem_element->len);
	mem_list_del(ptr);
	return;
}

void *realloc(void *ptr, size_t size)
{
	struct mem_list *mem_element = mem_list_find(ptr);
	if (!mem_element)
		return NULL;
	void *new = mremap(ptr, mem_element->len, size, 0);
	// remap failed
	if (new == MAP_FAILED) {
		// new mapping
		new = malloc(size);
		if(new == MAP_FAILED)
			return NULL;
		size_t min = size;
		if (min > mem_element->len)
			min = mem_element->len;
		// copy old memory
		memcpy(new, ptr, min);
		// unmap old memory
		munmap(mem_element->start, mem_element->len);
	}
	// replace mem_element mapping
	mem_element->start = new;
	mem_element->len = size;
	return mem_element->start;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	// check overflow
	size_t MAX_SIZE = 0;
	MAX_SIZE--;
	if ((MAX_SIZE / size) < nmemb)
		return NULL;
	struct mem_list *mem_element = mem_list_find(ptr);
	if (!mem_element)
		return NULL;
	void *new = mremap(ptr, mem_element->len, size * nmemb, 0);
	// remap failed
	if (new == MAP_FAILED) {
		// new mapping
		new = malloc(size * nmemb);
		if(new == MAP_FAILED)
			return NULL;
		size_t min = size * nmemb;
		if (min > mem_element->len)
			min = mem_element->len;
		// copy old memory
		memcpy(new, ptr, min);
		// unmap old memory
		munmap(mem_element->start, mem_element->len);
	}
	// replace mem_element mapping
	mem_element->start = new;
	mem_element->len = size * nmemb;
	return mem_element->start;
}
