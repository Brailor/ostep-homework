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
    int filedes[2];
    if (pipe(filedes) == -1)
    {
        err_exit("pipe fail");
    }
    pid_t fpid1 = _fork();

    if (fpid1 == 0)
    {
        // first child proc
        // this proc should set its FILE STDOUT to filedes[1]
        dup2(filedes[1], STDOUT_FILENO);
        printf("hello from first child\n");
    }
    else
    {
        // wait for first child to attach its stdout to pipe
        waitpid(fpid1, NULL, 0);
        pid_t fpid2 = _fork();

        if (fpid2 == 0)
        {
            // second child proc
            dup2(filedes[0], STDIN_FILENO);
            char buffer[BUFSIZ];
            read(STDIN_FILENO, buffer, BUFSIZ);
            printf("data read from other child process: %s", buffer);
        }
        else
        {
            // parent
            // wait for second child
            waitpid(fpid2, NULL, 0);
        }
    }

    return 0;
}