#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int size = 10; 

int main() {
    int arr[size];
    for (int i=0; i<size; i++) {
        arr[i] = rand() % 20;
    }
    bool swap = true;
    while (swap) {
        swap = false;
        for (int i=0; i<size-1; i++) {
            if (arr[i] < arr[i+1]) {
                int tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                swap = true;
            }
        }
    }
    printf("%i",arr[0]);
}

