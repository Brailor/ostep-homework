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
    // open a file
    int fd = open("./homework.output", O_CREAT | O_WRONLY, S_IRWXU);
    int rc = _fork();

    if (rc == 0)
    {
        printf("[child]\n");
        printf("\tfd is: %d\n", fd);
        printf("\twriting to file\n");
        char *data = "this is some data...\n coming from the child process\n";

        int res = write(fd, data, strlen(data));

        if (res < 0)
        {
            printf("\terror during writing to file...");
        }
    }
    else
    {
        // wait(NULL);
        printf("[parent]\n");
        printf("\tfd is: %d\n", fd);
        printf("\twriting to file\n");
        char *data = "this is some data...\n coming from the parent process\n";

        int res = write(fd, data, strlen(data));
        if (res < 0)
        {
            printf("\terror during writing to file...");
        }
        // close(fd);
    }
    return 0;
}