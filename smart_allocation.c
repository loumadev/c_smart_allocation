#include <stdlib.h>
#include <stdio.h>
#include "hashmap.h"
#include "smart_allocation.h"

struct hashmap_t *hashmap = NULL;

void* smart_malloc(size_t size) {
	if(!hashmap) hashmap = hashmap_create(SMART_ALLOCATOR_SIZE);

	void *ptr = malloc(size);
	hashmap_put(hashmap, (u_int64_t)ptr % SMART_ALLOCATOR_SIZE, ptr);

	return ptr;
}

int smart_free(void *ptr) {
	if(!hashmap) return 0;

	if(!hashmap_remove(hashmap, (u_int64_t)ptr % SMART_ALLOCATOR_SIZE)) return 0;
	free(ptr);

	return 1;
}

void smart_deallocate() {
	if(!hashmap) return;

	for(int i = 0; i < hashmap->size; i++) {
		struct hashmap_bucket_t *bucket = hashmap->buckets[i];
		struct hashmap_entry_t *entry = bucket->entry;

		while(entry) {
			struct hashmap_entry_t *next = entry->next;
			free(entry->value);
			entry = next;
		}
	}

	hashmap_destroy(hashmap);
}
