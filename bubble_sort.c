#include <stdio.h>

void swap(int* a, int* b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

void bubble_sort(int array[], int length) {
	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - 1 - i; j++) {
			if (array[j] > array[j + 1]) {
				swap(&array[j], &array[j + 1]);
			}
		}
	}
}

void print_array(int array[], int length) {
	for (int i = 0; i < length; i++) {
		printf(" %d ", array[i]);
	}
	printf("\n");
}

int main() {
	int array[] = {1, 3, 2, 10, 8, 1};
	int length = sizeof(array) / sizeof(array[0]);

	printf("Array normal:\n");
	print_array(array, length);

	bubble_sort(array, length);
	
	printf("Array ordenada:\n");
	print_array(array, length);

	return 0;
}
