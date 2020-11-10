#include <stdio.h>
#include <stddef.h>
#include <sys/mman.h>

#ifndef TC_MALLOC_H_
#define TC_MALLOC_H_

#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define HEAP_SIZE 100000
#define THREAD_SIZE 1024

void *heapStart;
void *heapEnd;

typedef struct node_t                                                                  {
 size_t size;
 struct node_t *nextPtr;
}node;

typedef struct header_t{
 size_t size;
 struct header_t *next;
 struct header_t *prev;
}header;

typedef struct free_block_head
{
 size_t size;
 struct free_block_head *next;
 struct free_block_head *prev;
}free_block_head_t;

void *tc_central_init();
void *tc_thread_init();
void *tc_malloc(size_t size);
void tc_free();

void *find_fit(size_t size);

#endif
