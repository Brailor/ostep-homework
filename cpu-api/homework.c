#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/fcntl.h>
#include <string.h>
#include <sys/syslimits.h>
#include <fcntl.h>

int _fork()
{
    int rc = fork();

    assert(rc >= 0);

    return rc;
}

int one()
{
    int x = 50;
    int rc = fork();

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

int two()
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

void three()
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
}

void four()
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
}

int main()
{
    // one();
    // two();
    // three();
    four();
}
