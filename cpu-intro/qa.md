# 1. -l 5:100,5:100
CPU utilization will be 100% since none of the intstructions are `io` which means the cpu can just run them sequentually.

# 2. -l 4:100,1:0 - how long will it take?
P0 will take 4 time since it does not have any `io` in it.
Then P1 will kick off, the it hits `io` (time: 1), then we wait for the `io` to finish (5, time: 6), then `io` done (1, time: 7)
Total time: P0,4 + P1,7 = 11

# 3. -l 1:0,4:100 - how long will it take?
P0 starts with (1, time: 1), then asks `io`, but since this time the order of processes are reversed we can do the other process which don't have `io` in it while we wait for P0's `io` to finish.
P1 starts when P0 starts to wait for `io`, (4, time: 5, `io` waiting left: 1).
Wait for P0's `io` to finish (1, time 7)
Total time is: 7

# 4 -l 1:0,4:100 -S SWITCH_ON_END
When setting the flag `SWITCH_ON_END` to true the system will not switch to other processes while waiting for `io`.
So what that means in this case, is that P0 will start, it hits `io` (1, time: 1), then it won't switch to P1, instead it will do nothing just waits for P0's `io` to finish (5, time: 6), when waiting for `io` to be done P0 can be finished as well (1, time: 7)
When P0 is finished P1 can start and finish its work (4, time: 11)
So essentially this example is the same as #2 just in reverse order. 
Total time: 11

# 5 -l 1:0,4:100 -S SWITCH_ON_IO
Since `SWITCH_ON_IO` is the default, this example is essentially the same as #3.
Total time: 7

# 6 -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER
This won't be ideal since the `IO_RUN_LATER` is set which means P0's `io` utilization will be bad, because P0 will start, immediatly ask for `io`,
then we switch to P1, complete it fully, by that time we could go back to P0 but since `IO_RUN_LATER` is set we will continue with P2 and P3 to finish, and then we go back to P0. At that point P0 wil have 2 `ios` left which means the `cpu` will be idle for both of them.
A better approach would be to immediatly switch back to the process that had `io`, in this case P0, then while we are waiting for its `io` then start running P2 and on.

# 7 -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE
This will be much better than #6, since we are always switiching back to P0 to issue the `io` and while we wait for that we can run P2 and P3. Resulting less time and better utilization of `cpu` and `io`.
> Why might running a process that just com- pleted an I/O again be a good idea?

This is a great question, my theory is that once a process has `io` in it, there is a good chance it will contain other `io` related instructions in it, so our best bet is to go back to it immediatly.
