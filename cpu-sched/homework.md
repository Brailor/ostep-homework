Tturnaround = Tcompletion - Tarrival

Tresponse = Tfirstrun - Tarrival

## 1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.

- SJF (Shortest-Job-First):

  [t 0] run job 0 for 200 (DONE at 200)

  [t 200] run job 1 for 200 (DONE at 400)

  [t 400] run job 2 for 200 (DONT at 600)

  - Job 0 Response: 0, Turnaround: 200
  - Job 1 Response: 200, Turnaround: 400
  - Job 2 Response: 400, Turnaround: 600
  - average: response: 200, turnaround: 400

- FIFO:

  [t 0] run job 0 for 200 (DONE at 200)

  [t 200] run job 1 for 200 (DONE at 400)

  [t 400] run job 2 for 200 (DONT at 600)

  - Job 0 Response: 0, Turnaround: 200
  - Job 1 Response: 200, Turnaround: 400
  - Job 2 Response: 400, Turnaround: 600
  - average: r: 200, t:400

## 2. Now do the same but with jobs of different lengths: 100, 200, and 300.

- SJF(job0=100, job1=200, job2=200):

  [t 0] run job 0 for 100 (DONE at 100)

  [t 100] run job 1 for 200 (DONE at 300)

  [t 300] run job 2 for 300 (DONE at 400)

  - job 0 response: 0, turnaround: 100
  - job 1 response: 100, turnaround: 300
  - job 2 response: 300, turnaround: 600
  - average: r:133, t: 333

- FIFO:

  [t 0] run job 0 for 100 (DONE at 100)

  [t 100] run job 1 for 200 (DONE at 300)

  [t 300] run job 2 for 300 (DONE at 400)

  - job 0 response: 0, turnaround: 100
  - job 1 response: 100, turnaround: 300
  - job 2 response: 300, turnaround: 600
  - average: r:133, t: 333

## 3. Now do the same, but also with the RR scheduler and a time-slice of 1.

- RR (round-robin):

  [t 0] run job 0 for 1 (PAUSE at 1)

  [t 1] run job 1 for 1 (PAUSE at 2)

  [t 2] run job 2 for 1 (PAUSE at 3)

  [t 3] run job 0 for 1 (PAUSE at 4)

  ...

  [t x] run job 0 for 1 (DONE at x)

  [t x+1] run job 1 for 1

  [t x+2] run job 2 for 1

  ...

  - job 0 r: 0, t: x
  - job 1 r: 1, t ?
  - job 2 r: 2, t: ?

## 4. For what types of workloads does SJF deliver the same turnaround times as FIFO?

It delivers the same turnaround times for jobs that have equal "lengths".

## 5. For what types of workloads and quantumlengths does SJF deliver the same response times as RR?

SJF will deliver the same response time if the lenght of the jobs equal to the quantumlenghts in case of RR.

## 6. What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?

I would assume that the response time will increase by the lenghts of the previous jobs, so it adds up drasticly when job lenghts increase.

## 7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?

With quantum lenghts increasing response times are also increasing.
TODO: equation
