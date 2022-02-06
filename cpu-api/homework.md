Questions

1. Write a program that calls fork(). Before calling fork(), have the
   main process access a variable (e.g., x) and set its value to some-
   thing (e.g., 100). What value is the variable in the child process?
   What happens to the variable when both the child and parent change
   the value of x?
2. Write a program that opens a file (with the open() system call)
   and then calls fork() to create a new process. Can both the child
   and parent access the file descriptor returned by open()? What
   happens when they are writing to the file concurrently, i.e., at the
   same time?
3. Write another program using fork(). The child process should
   print “hello”; the parent process should print “goodbye”. You should
   try to ensure that the child process always prints first; can you do
   this without calling wait() in the parent?
4. Write a program that calls fork() and then calls some form of
   exec() to run the program /bin/ls. See if you can try all of the
   variants of exec(), including (on Linux) execl(), execle(),
   execlp(), execv(), execvp(), and execvpe(). Why do
   you think there are so many variants of the same basic call?
5. Now write a program that uses wait() to wait for the child process
   to finish in the parent. What does wait() return? What happens if
   you use wait() in the child?
   - `wait` called in the parent will give back the child's process id
   - nothing seem to happen when using `wait` inside the children, other than the returned value is -1
     - altough if I `wait` inside the children it seems like that the parent will be called first
     - but I can't verify this, because it does the same even if I don't use `wait` inside the children
6. Write a slight modification of the previous program, this time us-
   ing waitpid() instead of wait(). When would waitpid() be
   useful?
   - `waitpid` allows more fine grain control over which child processes should we wait for
   - it also has an `options` parameter for even more control
7. Write a program that creates a child process, and then in the child
   closes standard output (STDOUT FILENO). What happens if the child
   calls printf() to print some output after closing the descriptor?
   - no output is printed to the console
   - I wonder where the output of `printf` goes in this case
8. Write a program that creates two children, and connects the stan-
   dard output of one to the standard input of the other, using the
   pipe() system call.
