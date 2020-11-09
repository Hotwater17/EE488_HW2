#include <stdio.h>

#include "tc_malloc.h"
//#include "tc_malloc.c"

int main()
{

 void *heapStart = tc_central_init();
 void *thread1 = tc_thread_init();
 void *ptr1 = tc_malloc(10);
 void *ptr2 = tc_malloc(20);
 void *ptr3 = tc_malloc(30);
 void *ptr4 = tc_malloc(1000);
 void *fitPtr;
 header *ptrstruct = ptr1;
 printf("%p %p %p %ld %p \n", heapStart, thread1, ptr1, ptrstruct->size, fitPtr);
 tc_free(ptr1);
 printf(" FREEING ptr1 \n");
 fitPtr = find_fit(ALIGN(25)+SIZE_T_SIZE);
 printf("Freeing ptr2 and 4 \n");
tc_free(ptr2);
 tc_free(ptr4);
 fitPtr = find_fit(ALIGN(25)+SIZE_T_SIZE);
 printf("%p %ld %p \n", ptrstruct, ptrstruct->size, fitPtr);
 return 0;
}

