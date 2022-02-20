# Memory Address Space
`memory-user` is a program which accepts 1 argument. This argument controlls how much memory (in megabytes) the program will consume.


Usage:
```sh
./memory-user 256
```


# Questions
## 1. The first Linux tool you should check out is the very simple tool free. First, type man free and read its entire manual page; it’s short, don’t worry!
Note: `free` is a Linux only tool.
## 2. Now, run free, perhaps using some of the arguments that might be useful (e.g., -m, to display memory totals in megabytes). How much memory is in your system? How much is free? Do these numbers match your intuition?
```sh
vagrant@vm-ostep:~/ostep$ free -h
              total        used        free      shared  buff/cache   available
Mem:          1.9Gi       1.3Gi       417Mi       2.0Mi       278Mi       544Mi
Swap:         1.9Gi       8.0Mi       1.9Gi
```
2GB memory is expected, becuase of the vagrant configuration is set to be 2.

## 3. Next, create a little program that uses a certain amount of memory, called memory-user.c. This program should take one command- line argument: the number of megabytes of memory it will use. When run, it should allocate an array, and constantly stream through the array, touching each entry. The program should do this indefi- nitely, or, perhaps, for a certain amount of time also specified at the command line.

## 4. Now, while running your memory-user program, also (in a dif- ferent terminal window, but on the same machine) run the free tool. How do the memory usage totals change when your program is running? How about when you kill the memory-user program? Do the numbers match your expectations? Try this for different amounts of memory usage. What happens when you use really large amounts of memory?
Segmentation fault occurs when the given size to memory-user is larger then the available memory.
## 5. Let’s try one more tool, known as pmap. Spend some time, and read the pmap manual page in detail.

## 6. To usepmap, you haveto know the process ID of the process you’re interested in. Thus, first run ps auxw to see a list of all processes; then, pick an interesting one, such as a browser. You can also use your memory-user program in this case (indeed, you can even have that program call getpid() and print out its PID for your convenience).

## 7. Now run pmap on some of these processes, using various flags(like -X) to reveal many details about the process. What do you see? How many different entities make up a modern address space, as opposed to our simple conception of code/stack/heap?
We can see diffent kind of c utils as well such as: libc, libm, ld.

## 8. Finally, let’s run pmap on your memory-user program, with different amounts of used memory. What do you see here? Does the output from pmap match your expectations?
One interesting note is that `free` does not show the memory usage in real time, but as the program runs the memory size increase as opposed to `pmap` which shows how much memory the program will consume even when the program just started.

Also I noted that when I iterate over the array and access each element - as suggested in the 2. question - and I don't use the current element in some kind of way (for example print it out), then the memory footprint of the program is negliable. I guess this is some compiler optimalization, which notices that the accessed element is not being used, so it just ignores that step? (check this out)