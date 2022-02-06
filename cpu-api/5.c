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
    int f_pid = _fork();

    if (f_pid == 0)
    {
        //child (new process)
        int idk = wait(NULL);
        printf("hello from child (pid: %d)\n", (int)getpid());
        printf("the value of `wait` inside the child process is: %d\n", idk);
    }
    else
    {
        //parent
        int child_pid = wait(NULL);
        printf("parent (pid: %d)\n", (int)getpid());
        printf("the value of `wait` is: %d\n", child_pid);
    }
    return 0;
}