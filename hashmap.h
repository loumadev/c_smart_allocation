struct hashmap_entry_t {
	int key;
	void *value;
	struct hashmap_entry_t *next;
};

struct hashmap_bucket_t {
	int size;
	struct hashmap_entry_t *entry;
};

struct hashmap_t {
	int size;
	struct hashmap_bucket_t **buckets;
};

struct hashmap_t* hashmap_create(int size);
void hashmap_destroy(struct hashmap_t *hashmap);
int hashmap_hash(struct hashmap_t *hashmap, int key);
void hashmap_put(struct hashmap_t *hashmap, int key, void *value);
void* hashmap_get(struct hashmap_t *hashmap, int key);
int hashmap_remove(struct hashmap_t *hashmap, int key);
void hashmap_clear(struct hashmap_t *hashmap);
void print_hashmap(struct hashmap_t *hashmap);
