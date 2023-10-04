#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int DEFAULT_SIZE = 10;

int *list;
size_t length;
size_t capacity;

// Checks if an error occurred while dynamic allocating memory.
void check_error(void) 
{
	if (list == NULL) 
	{
		fprintf(stderr, "Memory error!\n");
		exit(1);
	}
}

// Creates empty dynamic array, with specified capacity.
void initialize(const size_t wanted_capacity) 
{
	printf("Empty capacity! Initializing!\n");
	list = calloc(wanted_capacity, sizeof(int));
	check_error();
	length = 0;
	capacity = wanted_capacity;
}

// Checks if the number of elements of the array equals the capacity.
// If that's true, there's no more space to append elements,
// then it increases the allocated memory.
void check_capacity(void) 
{
	if (length == capacity) 
	{
		printf("Not enough space! Reallocating!\n");
		capacity += DEFAULT_SIZE;
		list = realloc(list, capacity * sizeof(int));
		check_error();
	}
}

// Inserts element on the last possible spot, that has the same value of
// the number of elements
void append(int element) 
{
	if (capacity == 0) 
	{
		initialize(DEFAULT_SIZE);
		check_error();
	}

	check_capacity();
	list[length] = element;
	length++;
	printf("Num of elements: %lu\n", length);
	printf("Size: %lu\n", capacity);
}

void print_list(void) 
{
	if (length == 0) 
	{
		printf("The list is empty!\n");
		return;
	}

	for (int i = 0; i < length; i++) 
	{
		printf(" [%d] ", list[i]);
	}

	printf("\n");
}

int sum_list(void) 
{
	int sum = 0;

	for (int i = 0; i < length; i++) 
	{
		sum += list[i];
	}

	return sum;
}

void destroy(void) 
{
	free(list);
	list = NULL;
	length = 0;
	capacity = 0;
}

int main(void) 
{
	int typed_number;

	do {
		printf("Type a number you want to sum: (0 terminates the program)\n");
		scanf(" %d", &typed_number);
		if (typed_number != 0) append(typed_number);
	} while (typed_number != 0);
	
	printf("This is the list you created:\n");
	print_list();
	printf("This is the sum of the values:\n%d\n", sum_list());
	destroy();

	return 0;
}
