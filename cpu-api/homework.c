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
//uses `wait`, what is the return value of `wait`
//what happens if you use `wait` inside the children?
void five()
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
}

int six()
{
    int f_pid = _fork();

    if (f_pid == 0)
    {
        printf("hello from child (pid: %d)\n", (int)getpid());
    }
    else
    {
        //parent
        int child_pid = waitpid(f_pid, NULL, 0);
        printf("parent (pid: %d)\n", (int)getpid());
        printf("the value of `waitpid` is: %d\n", child_pid);
    }
    return 0;
}

int seven()
{
    int f_pid = _fork();

    if (f_pid == 0)
    {
        close(STDOUT_FILENO);
        printf("printing from child after closing STDOUT\n");
    }
    else
    {
        printf("parent (pid: %d)\n", (int)getpid());
    }

    return 0;
}

int eight()
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
int main()
{
    // one();
    // two();
    // three();
    // four();
    // five();
    // six();
    // seven();
    eight();
}
