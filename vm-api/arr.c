#include <stdlib.h>
#include <stdio.h>

int main() {
    int *arr = (int*)malloc(sizeof(int) * 100);

    arr[100] = 0;

    // free(arr);
    return 0;
}