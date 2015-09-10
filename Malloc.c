#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include "mem.h"

int 
main()
{
	int *a,*b,*c,*d;
	int count;
	
	a = (int*)my_malloc(sizeof(int)*40);
	if(a==NULL)
		printf("\n Malloc Failed\n");
	b = (int*)my_malloc(sizeof(int)*100);
	if(b==NULL)
		printf("\nMalloc Failed\n");
	c = (int*)my_malloc(sizeof(int)*80);
	if(c==NULL)
		printf("\nMalloc Failed\n");
	d = (int*)my_malloc(sizeof(int)*10);
	if(d==NULL)
		printf("\nMalloc Failed\n");

	if(a!=NULL)
	{
		for (count = 0; 40> count; ++count)
		{
			a[count] = count+1;
		}
	}
	hexdump();
	printf("Free space in heap = %d\n",(int)free_space_in_my_heap());
	my_free(b);
	printf("Free space in heap after freeing B = %d\n",(int)free_space_in_my_heap());
	a = (int*)my_realloc(a,sizeof(int)*90);
	hexdump();
	printf("Free space in heap = %d\n",(int)free_space_in_my_heap());
	my_free(a);
	printf("Free space in heap after freeing A= %d\n",(int)free_space_in_my_heap());
	a = (int*)my_calloc(sizeof(int),82);
	if(a!=NULL)
	{
		for (count = 0; 40> count; ++count)
		{
			a[count] = count+1;
		}
	}
	hexdump();
	printf("Free space in heap before defragmentation = %d\n",(int)free_space_in_my_heap());
	defragment_my_heap();
	printf("Free space in heap after defragmentation = %d\n",(int)free_space_in_my_heap());
	hexdump();
	return 0;
}


