#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

struct hashmap_t* hashmap_create(int size) {
	struct hashmap_t *hashmap = (struct hashmap_t*)malloc(sizeof(struct hashmap_t));
	hashmap->size = size;
	hashmap->buckets = (struct hashmap_bucket_t**)malloc(sizeof(struct hashmap_bucket_t*) * size);

	for(int i = 0; i < size; i++) {
		hashmap->buckets[i] = (struct hashmap_bucket_t*)malloc(sizeof(struct hashmap_bucket_t));
		hashmap->buckets[i]->size = 0;
		hashmap->buckets[i]->entry = NULL;
	}

	return hashmap;
}

void hashmap_destroy(struct hashmap_t *hashmap) {
	for(int i = 0; i < hashmap->size; i++) {
		struct hashmap_bucket_t *bucket = hashmap->buckets[i];
		struct hashmap_entry_t *entry = bucket->entry;

		while(entry) {
			struct hashmap_entry_t *next = entry->next;
			free(entry);
			entry = next;
		}

		free(bucket);
	}

	free(hashmap->buckets);
	free(hashmap);
}

int hashmap_hash(struct hashmap_t *hashmap, int key) {
	return key % hashmap->size;
}

void hashmap_put(struct hashmap_t *hashmap, int key, void *value) {
	int hash = hashmap_hash(hashmap, key);
	struct hashmap_bucket_t *bucket = hashmap->buckets[hash];
	struct hashmap_entry_t *entry = bucket->entry;

	while(entry) {
		if(entry->key == key) {
			entry->value = value;
			return;
		}

		entry = entry->next;
	}

	entry = (struct hashmap_entry_t*)malloc(sizeof(struct hashmap_entry_t));
	entry->key = key;
	entry->value = value;
	entry->next = bucket->entry;

	bucket->entry = entry;
	bucket->size++;
}

void* hashmap_get(struct hashmap_t *hashmap, int key) {
	int hash = hashmap_hash(hashmap, key);
	struct hashmap_bucket_t *bucket = hashmap->buckets[hash];
	struct hashmap_entry_t *entry = bucket->entry;

	while(entry) {
		if(entry->key == key) {
			return entry->value;
		}

		entry = entry->next;
	}

	return NULL;
}

int hashmap_remove(struct hashmap_t *hashmap, int key) {
	int hash = hashmap_hash(hashmap, key);
	struct hashmap_bucket_t *bucket = hashmap->buckets[hash];
	struct hashmap_entry_t *entry = bucket->entry;
	struct hashmap_entry_t *prev = NULL;

	while(entry) {
		if(entry->key == key) {
			if(prev) {
				prev->next = entry->next;
			} else {
				bucket->entry = entry->next;
			}

			free(entry);
			bucket->size--;
			return 1;
		}

		prev = entry;
		entry = entry->next;
	}

	return 0;
}

void hashmap_clear(struct hashmap_t *hashmap) {
	for(int i = 0; i < hashmap->size; i++) {
		struct hashmap_bucket_t *bucket = hashmap->buckets[i];
		struct hashmap_entry_t *entry = bucket->entry;

		while(entry) {
			struct hashmap_entry_t *next = entry->next;
			free(entry);
			entry = next;
		}

		bucket->size = 0;
		bucket->entry = NULL;
	}
}

void print_hashmap(struct hashmap_t *hashmap) {
	for(int i = 0; i < hashmap->size; i++) {
		struct hashmap_bucket_t *bucket = hashmap->buckets[i];
		struct hashmap_entry_t *entry = bucket->entry;

		while(entry) {
			printf("[%d] key: %d, value: %p\n", i, entry->key, entry->value);
			entry = entry->next;
		}
	}
}
