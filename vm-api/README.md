# Questions

## 1. First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you run this program?

The address of the pointer is 0x0.
On linux the pointer address is reported as: `nil`

## 2. Next, compile this program with symbol information included(with the -g flag). Doing so let’s put more information into the exe- cutable, enabling the debugger to access more useful information about variable names and the like. Run the program under the de- bugger by typing gdb null and then, once gdb is running, typing run. What does gdb show you?
The output of `gdb` is: 
```sh
(gdb) run
Starting program: /home/vagrant/ostep/homework/vm-api/null 
the address of num is: (nil)
[Inferior 1 (process 3827) exited normally]
```
Which is the same as if I would run the program normally.

## 3. Finally, use the `valgrind` tool on this program. We’ll use the `memcheck` tool that is a part of valgrind to analyze what happens. Run this by typing in the following: valgrind --leak-check=yes null. What happens when you run this? Can you interpret the output from the tool?
Output:
```sh
==4317== Memcheck, a memory error detector
==4317== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==4317== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==4317== Command: ./null
==4317== 
the address of num is: (nil)
==4317== 
==4317== HEAP SUMMARY:
==4317==     in use at exit: 0 bytes in 0 blocks
==4317==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==4317== 
==4317== All heap blocks were freed -- no leaks are possible
==4317== 
==4317== For counts of detected and suppressed errors, rerun with: -v
==4317== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
This basically says that there were 1 memory allocations which was automatically free-ed and it allocated 1024 bytes (1kb) of memory.

What is interesting if I modify the code to:
```c
    ...
    int *num = malloc(sizeof(int));
    ...
```
Then `valgrind` reports the following:
```sh
==5013== Memcheck, a memory error detector
==5013== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==5013== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==5013== Command: ./null
==5013== 
the address of num is: 0x4b93040
==5013== 
==5013== HEAP SUMMARY:
==5013==     in use at exit: 4 bytes in 1 blocks
==5013==   total heap usage: 2 allocs, 1 frees, 1,028 bytes allocated
==5013== 
==5013== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==5013==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==5013==    by 0x109152: main (null.c:6)
==5013== 
==5013== LEAK SUMMARY:
==5013==    definitely lost: 4 bytes in 1 blocks
==5013==    indirectly lost: 0 bytes in 0 blocks
==5013==      possibly lost: 0 bytes in 0 blocks
==5013==    still reachable: 0 bytes in 0 blocks
==5013==         suppressed: 0 bytes in 0 blocks
==5013== 
==5013== For counts of detected and suppressed errors, rerun with: -v
==5013== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
4 bytes of memory was allocated, which is expected given in C an int is 4 byte long.
The total memory allocated is now: 1028 bytes, 4 bytes more then the previous time, I wonder why it allocates 1024 bytes?


## 4. Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind (again with the --leak-check=yes flag)?
- `gdb` doesn't seem to report any kind of error.
- `valgrind`:
```sh
==12433== Command: ./no-free.out
==12433== 
==12433== 
==12433== HEAP SUMMARY:
==12433==     in use at exit: 8 bytes in 1 blocks
==12433==   total heap usage: 1 allocs, 0 frees, 8 bytes allocated
==12433== 
==12433== 8 bytes in 1 blocks are definitely lost in loss record 1 of 1
==12433==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==12433==    by 0x109146: main (no-free.c:5)
==12433== 
==12433== LEAK SUMMARY:
==12433==    definitely lost: 8 bytes in 1 blocks
==12433==    indirectly lost: 0 bytes in 0 blocks
==12433==      possibly lost: 0 bytes in 0 blocks
==12433==    still reachable: 0 bytes in 0 blocks
==12433==         suppressed: 0 bytes in 0 blocks
==12433== 
==12433== For counts of detected and suppressed errors, rerun with: -v
==12433== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
`valgrind` correctly reports that 8 bytes of memory is not freed (I used `malloc(sizeof(double)`)) and is definetely lost.


## 5. Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?
[code](arr.c)
The program does not crash at all, altough running `valgrind` reports the error:
```sh
==13550== Command: ./arr.out
==13550== 
==13550== Invalid write of size 4
==13550==    at 0x109165: main (arr.c:7)
==13550==  Address 0x4a101d0 is 0 bytes after a block of size 400 alloc'd
==13550==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==13550==    by 0x109156: main (arr.c:5)
==13550== 
==13550== 
==13550== HEAP SUMMARY:
==13550==     in use at exit: 0 bytes in 0 blocks
==13550==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==13550== 
==13550== All heap blocks were freed -- no leaks are possible
==13550== 
==13550== For counts of detected and suppressed errors, rerun with: -v
==13550== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## 6. Create a program that allocates an array of integers(as above), frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use valgrind on it?
[code](arr2.c)
Again, the program does not crush, nor report any kind of errors, it just prints out 0 (the default value for the data type?).

`valgrind` once again correctly reports the error:
```sh
=13824== Command: ./arr2.out
==13824== 
==13824== Invalid read of size 4
==13824==    at 0x10917F: main (arr2.c:9)
==13824==  Address 0x4a10044 is 4 bytes inside a block of size 400 free'd
==13824==    at 0x48369AB: free (vg_replace_malloc.c:530)
==13824==    by 0x109176: main (arr2.c:7)
==13824==  Block was alloc'd at
==13824==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==13824==    by 0x109166: main (arr2.c:5)
==13824== 
trying to print the 2nd element of the array: 0
==13824== 
==13824== HEAP SUMMARY:
==13824==     in use at exit: 0 bytes in 0 blocks
==13824==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==13824== 
==13824== All heap blocks were freed -- no leaks are possible
==13824== 
==13824== For counts of detected and suppressed errors, rerun with: -v
==13824== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## 7. Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?
[code](arr3.c)
This does crash even without running any kind of tool.
```sh
free(): invalid pointer
Aborted
```

`valgrind` obviously reports it as well:
==14134== Command: ./arr3.out
==14134== 
==14134== Invalid free() / delete / delete[] / realloc()
==14134==    at 0x48369AB: free (vg_replace_malloc.c:530)
==14134==    by 0x10916C: main (arr3.c:7)
==14134==  Address 0x4a10104 is 196 bytes inside a block of size 400 alloc'd
==14134==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==14134==    by 0x109156: main (arr3.c:5)
==14134== 
==14134== 
==14134== HEAP SUMMARY:
==14134==     in use at exit: 400 bytes in 1 blocks
==14134==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==14134== 
==14134== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==14134==    at 0x483577F: malloc (vg_replace_malloc.c:299)
==14134==    by 0x109156: main (arr3.c:5)
==14134== 
==14134== LEAK SUMMARY:
==14134==    definitely lost: 400 bytes in 1 blocks
==14134==    indirectly lost: 0 bytes in 0 blocks
==14134==      possibly lost: 0 bytes in 0 blocks
==14134==    still reachable: 0 bytes in 0 blocks
==14134==         suppressed: 0 bytes in 0 blocks
==14134== 
==14134== For counts of detected and suppressed errors, rerun with: -v
==14134== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```sh


## 8. Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use realloc() to manage the vector. Use an array to store the vectors elements; when a user adds an entry to the vector, use realloc() to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use valgrind to help you find bugs.

## 9. Spend more time and read about using `gdb` and `valgrind`. Knowing your tools is critical, spend the time and learn how to become an expert debugger in the UNIX and C environment.

## Notes

`gdb` didn't work on my (Mac) machine out of the box, it threw this error:

```sh
Unable to find Mach task port for process-id 12021: (os/kern) failure (0x5).
 (please check gdb is codesigned - see taskgated(8))
```

Which led me to this site: http://sourceware.org/gdb/wiki/BuildingOnDarwin

### TIL: `valgrind` is a linux specific tool

There is however a macos port here: https://github.com/LouisBrunner/valgrind-macos

The sad thing is that this port does not work currently with macos Big Sur and Monterey.

> Better to use a Linux VM at this point to do this homework.
