void* my_malloc(size_t);
void my_free(void*);
void* my_realloc(void* ptr,size_t size);
void* my_calloc(size_t n,size_t size);
void defragment_my_heap(void);
size_t free_space_in_my_heap(void);
void hexdump(void);

#define HEAP_SIZE 2000
char StaticMemory[HEAP_SIZE];
