# Questions

## 1. Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.

## 2. How would you run the scheduler to reproduce each of the examples in the chapter?

- 8.2:
  - `$ ./mlfq.py -n 3 -Q 10,10,200 --jlist 0,200,0`
- 8.3:
  - `$ ./mlfq.py -n 3 -Q 10,10,80 --jlist 0,200,0:100,20,0`
- 8.4:
  - `$ ./mlfq.py -n 3 -Q 10,10,80 --jlist 0,180,0:50,20,1`
- 8.5:
  - w/o boost: `$ ./mlfq.py -n 3 -Q 10,10,80 --jlist 0,200,0:100,50,5:100,50,5 -S `
  - note: I don't know how to limit the overall time to for example to be 200ms
  - w/ boost: `$ ./mlfq.py -n 3 -Q 10,10,80 --jlist 0,150,0:100,50,5:100,50,5 -S -B 50`
- 8.6:
  - no gaming tolerance: `$ ./mlfq.py -n 3 -Q 10,10,80 --jlist 0,170,0:80,80,9 -S -i 1`
  - w/ gaming tolerance: `$ ./mlfq.py -n 3 -Q 10,10,80 --jlist 0,170,0:80,80,9 -i 1 -c`
- 8.7:
  - the program has a bug in it, but it should be: `$ ./mlfq.py -n 3 -Q 10,20,40 -A 20,40,80 --jlist 0,100,0:0,100,0`

## 3. How would you configure the scheduler parameters to behave just like a round-robin scheduler?

Basically just configure it to have 1 queue, and a fixed quantum time length, something like this:
`$ ./mlfq.py -n 1 -q 20 --jlist 0,50,0:0,50,0:0,50,0`

## 4. Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the -S flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.

`$ ./mlfq.py -n 3 -q 10 -S --jlist 10,100,9:0,100,0 -i 1`

## 5. Given a system with a quantum length of 10ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the -B flag) in order to guarantee that a single long- running (and potentially-starving) job gets at least 5% of the CPU?

## 6. One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the -I flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.
