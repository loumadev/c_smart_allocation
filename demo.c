#include <stdio.h>
#include "smart_allocation.h"

struct my_struct {
	int number;
};

struct my_struct* new_struct() {
	struct my_struct *my_struct = smart_malloc(sizeof(struct my_struct));
	my_struct->number = 123;

	return my_struct;
}

int my_function() {
	for(int i = 0; i < 10; i++) {
		int *ptr = smart_malloc(sizeof(int));
		*ptr = i;

		// Randomly free some memory
		if(i % 2) smart_free(ptr);
	}
}

int main(int argc, char **argv) {
	// Allocate a singe int
	int *ptr = smart_malloc(sizeof(int));
	*ptr = 10;
	printf("> ptr: %p, *ptr: %d\n", ptr, *ptr);

	// Allocate a structure
	struct my_struct *my_struct = new_struct();
	printf("> my_struct: %p, my_struct->number: %d\n", my_struct, my_struct->number);

	// Allocate bunch of integers
	my_function();

	// Clean up everyting by just a singe function call
	smart_deallocate();
	return 0;
}


