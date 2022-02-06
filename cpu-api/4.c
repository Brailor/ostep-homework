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
    int rc = _fork();

    if (rc == 0)
    {
        // child
        // char *exec_args[3] = {
        //     strdup("ls"),
        //     strdup("/Users"),
        //     NULL};

        // execvp(exec_args[0], exec_args);
        char *string_arg = strdup("/Users");
        execlp(strdup("ls"), string_arg);
    }
    else
    {
        // parent
        printf("parent \n");
    }
    return 0;
}