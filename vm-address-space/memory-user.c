#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("[usage]: ./memory-user size\n");
        exit(0);
    }
    char *endptr;
    int size = (int)strtol(argv[1], &endptr, 10);
    printf("given size is: %d\n", size);
    int item_count = (size * 10000) / sizeof(double);
    double arr[item_count];
    printf("size of arr is: %ld\n", sizeof(arr));
    printf("PID: %d\n", (int)getpid());

    while(1) {
        for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
            arr[i]++;
            // if I do nothing with the element, then the memory won't be allocated for some reason!
            printf("val is: %f\n", arr[i]);
        }
    }
    return 0;
}