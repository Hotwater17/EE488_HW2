
#include "tc_malloc.h"
/*
#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))*/
/*
typedef struct node_t
{
 size_t size;
 struct node_t *nextPtr;
}node;

typedef struct header_{
 size_t size;
}header;
*/
void *tc_central_init()
{
 /*Initialize central heap and return a pointer to first address of free list */
 //Look at mmap();
 node *head = mmap(NULL, ALIGN(HEAP_SIZE), PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE,
			-1,0);

 head->size = HEAP_SIZE-sizeof(node);
 head->nextPtr = NULL;

 heapStart = head;
 heapEnd = heapStart + HEAP_SIZE;
 printf("Start: %p End: %p \n", heapStart, heapEnd);
 return head;
}

void *tc_thread_init()
{
 /*Create a thread free list and return a pointer to start of free list*/
 node * threadNode = mmap(NULL,THREAD_SIZE,PROT_READ|PROT_WRITE,
				 MAP_ANON|MAP_PRIVATE, -1, 0);

 threadNode->size = THREAD_SIZE-sizeof(node);
 threadNode->nextPtr = NULL;

 return threadNode;
}

void *tc_malloc(size_t size)
{
 /*Allocate an object of size and return a pointer to it*/
 size_t alignedSize = ALIGN(size + SIZE_T_SIZE);
 //header * head = mmap(NULL, alignedSize, PROT_READ|PROT_WRITE,
 //                                MAP_ANON|MAP_PRIVATE, -1, 0);
 header *head = find_fit(alignedSize);
 if(head) head->size = alignedSize | 1;
 else printf("Not enough heap space \n");
 head->next = (void *)head+(head->size & ~1L);
 return head;
}

void tc_free(void *ptr)
{
 /*deallocate *ptr object*/
  header *head = ptr;
  head->size = head->size & ~1L;
  //Coalesce
  printf("next %p \n", head->next);
  head->next = (void *) head + head->size;
  if((void *)head->next <= (void *)heapEnd && !(head->next->size &1))
  {
   head->size += head->next->size;
  }
}

void *find_fit(size_t fitSize)
{
 header *head = heapStart;
 while((void *)head < (void *)heapEnd)
 {
 printf("Adr: %p size: %ld fit: %ld \n", head, head->size, fitSize);
  if(!(head->size & 1) && (head->size >= fitSize || head->size == 0))
  {
   printf("Found free fit at %p \n", head);
   return head;
  }
printf("head: %p size: %ld Head+size: %p \n", head, head->size, (void *)head+head->size);
head =  (void *)head + (head->size & ~1L);
 printf("%p \n", head);
 }
 printf("Space not found \n");
 return NULL;
}
