#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/fcntl.h>
#include <string.h>
#include <sys/syslimits.h>
#include <fcntl.h>

void err_exit(char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(1);
}

int _fork()
{
    int rc = fork();

    if (rc == -1)
    {
        err_exit("fork failed");
    }

    return rc;
}

int main(int argc, char *argv[])
{
        int fildes[2];
    if (pipe(fildes) == -1)
    {
        fprintf(stderr, "pipe error\n");
        exit(1);
    };

    int rc = _fork();

    if (rc == 0)
    {
        //  child

        printf("hello\n");
        write(fildes[1], strdup("child"), 5);
        close(fildes[1]);
    }
    else
    {
        // parent
        // parent should wait for child to finish
        // but without using `wait`
        char *msg = NULL;
        read(fildes[0], msg, 5);
        close(fildes[0]);
        printf("goodbye\n");
    }
    return 0;
}