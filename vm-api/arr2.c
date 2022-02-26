#include <stdlib.h>
#include <stdio.h>

int main() {
    int *arr = (int*)malloc(sizeof(int) * 100);

    free(arr);

    printf("trying to print the 2nd element of the array: %d\n", arr[1]);
    
    return 0;
}