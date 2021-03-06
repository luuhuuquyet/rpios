#ifndef LIB_H
#define LIB_H

#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>
#include "mmio.h"

#define panic(format, ...) \
do { \
	cons->cprintf(format, ##__VA_ARGS__); \
	while (1) {}; \
} while(0)

#define printk(format, ...) \
do { \
	cons->cprintf(format, ##__VA_ARGS__); \
} while(0)

#if DEBUG
#define dprintk(format, ...) \
do { \
	cons->cprintf("[%s:%d] ", __func__, __LINE__); \
	cons->cprintf(format, ##__VA_ARGS__); \
} while(0)
#else
#define dprintk(format, ...) \
do { \
} while(0)
#endif

#define bug_on(cond) \
do { \
	if (!cond)  { \
		asm volatile(".word 0xdeaddead"); \
	} \
} while(0)

size_t strlen(const char* str);
extern "C" int memcmp(const void *s1, const void *s2, size_t n);
extern "C" void *memcpy(void *dst, const void *src, size_t n);
extern "C" void *memmove(void *dst, const void *src, size_t n);
int str_to_int(const char *str);
int pow(int x, unsigned int y);
char* int_to_str(char *str, unsigned long val, int base);
uint32_t div(uint32_t n, uint32_t d);
char* itos(char *b, int i);
extern "C" void memset(void *b, const unsigned char c, int len);

/* Rounding operations (work only when n is a power of 2) */
static inline uint32_t round_down(uint32_t a, uint32_t n)
{
	return a - a % n;
};

static inline uint32_t round_up(uint32_t a, uint32_t n)
{
	return round_down(a + (n - 1), n);
};

static inline int is_pow_of_two(uint32_t x)
{
	return ((x != 0) && !(x & (x - 1)));
}

#endif
