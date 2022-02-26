#include <stdlib.h>
#include <stdio.h>

int main() {
    int *arr = (int*)malloc(sizeof(int) * 100);

    free(&arr[49]);
    
    return 0;
}