// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	if (destination == NULL)
        return NULL;
	char *iter = destination;
	while (*source) {
		*iter = *source;
		iter++;
		source++;
	}
	*iter = '\0';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	if (destination == NULL)
        return NULL;
	char *temp = destination;
	size_t i = 0;
	while (*source && i < len) {
		*temp = *source;
		temp++;
		source++;
		i++;
	}
	while (i < len) {
		*temp = '\0';
		temp++;
		i++;
	}
	return destination;
}

char *strcat(char *destination, const char *source)
{
	char *dest = destination;
	while (*dest)
		dest++;
	while (*source) {
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	char *dest = destination;
	while (*dest)
		dest++;
	size_t i = 0;
	while (*source &&  i < len) {
		*dest = *source;
		dest++;
		source++;
		i++;
	}
	*dest = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2) {
		if (*str1 != *str2)
			return *str1 - *str2;
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	size_t i = 0;
	while (*str1 && *str2 && i < len) {
		if (*str1 != *str2)
			return *str1 - *str2;
		str1++;
		str2++;
		i++;
	}
	if (i == len)
		return 0;
	else
		return *str1 - *str2;
}

size_t strlen(const char *str)
{
	size_t i = 0;
	while (*str) {
		str++;
		i++;
	}
	return i;
}

char *strchr(const char *str, int c)
{
	while (*str) {
		if (*str == c)
			return (char *) str;
		str++;
	}
	if (*str == c)
		return (char *) str;
	return NULL;
}

char *strrchr(const char *str, int c)
{
	// start from end of string
	char *end = (char *) str;
	while (*end)
		end++;
	// go backwards
	while (end != str) {
		if (*end == c)
			return end;
		end--;
	}
	// check first character
	if (*end == c)
		return end;
	else
		return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	char *str = (char *) haystack;
	while (*str) {
		if (*str == *needle) {
			int ok = 1;
			char *hay = str;
			char *need = (char *) needle;
			// check if substring is needle
			while (*hay && *need) {
				// different than needle
				if (*hay != *need) {
					ok = 0;
					break;
				}
				hay++;
				need++;
			}
			// if strings "equal" and
			// needle has ended
			if (ok == 1 && *need == '\0')
				return str;
		}
		str++;
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	char *str = (char *) haystack;
	// end of haystack
	while (*str)
		str++;
	while (str != haystack) {
		if (*str == *needle) {
			int ok = 1;
			char *hay = (char *) str;
			char *need = (char *) needle;
			// check if substring is needle
			while (*hay && *need) {
				// different than needle
				if (*hay != *need) {
					ok = 0;
					break;
				}
				hay++;
				need++;
			}
			// if strings "equal" and
			// needle has ended
			if (ok == 1 && *need == '\0')
				return str;
		}
		str--;
	}
	return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	void *modify = destination;
	while (num--) {
		*(char *) modify = *(char *) source;
		modify++;
		source++;
	}
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	void *modify = destination;
	while (num--) {
		*(char *) modify = *(char *) source;
		modify++;
		source++;
	}
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	char *p1 = (char *) ptr1;
	char *p2 = (char *) ptr2;
	while (num--) {
		if (*p1 != *p2)
			return *p1 - *p2;
		p1++;
		p2++;
	}
	return 0;
}

void *memset(void *source, int value, size_t num)
{
	unsigned char byte = (char) value;
	char *src = (char *)source;
	while (num--) {
		*(char *) src = byte;
		src++;
	}
	return source;
}
