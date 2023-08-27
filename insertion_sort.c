#include <stdio.h>

int main() {
    int array[] = {1, 5, 2, 7, 4};
    int length = sizeof(array) / sizeof(array[0]);

    for (int j = 1; j < length; j++) {
        int key = array[j];
        int i = j - 1;
        while (i >= 0 && array[i] > key) {
            array[i + 1] = array[i];
            i--;
        }
        array[i + 1] = key;
    }

    for (int i = 0; i < length; i++) {
        printf("Posicao %d: %d\n", i, array[i]);
    }

    return 0;
}