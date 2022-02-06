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

pid_t _fork()
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
    int x = 50;
    int rc = _fork();

    if (rc < 0)
    {
        fprintf(stderr, "forking failed!\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child process
        x = 30;
        printf("[child]\n");
        printf("\tthe value of x is: %d\n", x);
        printf("\tref to x: (%p)\n", &x);
    }
    else
    {
        //  parent
        x = 100;
        int rc_wait = wait(NULL);
        printf("[parent]\n");
        printf("\tthe value of x is: %d\n", x);
        printf("\tref to x: (%p)\n", &x);
    }

    return 0;
}