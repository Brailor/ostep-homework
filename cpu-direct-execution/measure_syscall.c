#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../intro/common.h"

// note:
// this only can measure
int main()
{
    printf("time: %f\n", GetTime());
    int fd = open("./README.md", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    struct timeval start_time, end_time;
    int syscall_count = 10000;

    gettimeofday(&start_time, NULL);

    for (int i = 0; i < syscall_count; i++)
    {
        read(fd, NULL, 0);
    }

    gettimeofday(&end_time, NULL);

    double start = start_time.tv_sec * 100000 + start_time.tv_usec;
    double end = end_time.tv_sec * 100000 + end_time.tv_usec;
    printf("started at: (%f), ended at: (%f), delta: (%f)\n", start, end, (end - start));
    printf("1 operation took: %f microseconds\n", (end - start) / syscall_count);

    return 0;
}