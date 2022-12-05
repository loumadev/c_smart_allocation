#define SMART_ALLOCATOR_SIZE 100

void* smart_malloc(size_t size);
int smart_free(void *ptr);
void smart_deallocate();
