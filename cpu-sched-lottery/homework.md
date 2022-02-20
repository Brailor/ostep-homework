# Questions

## 1. Compute the solutions for simulations with 3 jobs and random seeds of 1, 2, and 3.

- s=1, tickets: 84 + 25 + 44 = 153
  1. w: (651593 % 153)=119 -- j: 2 -- j2: 3
  2. w: (788724 % 153)=9 -- j: 0 -- j0: 0
  3. w: (93859 % 79)=7 j: 1 -- j1: 6
  4. w: (28347 % 79)=65 j: 2 -- j2: 2
  5. w: (835765 % 79)=24 j: 1 -- j1: 5
  6. w: (432767 % 79)=5 j: 1 -- j1: 4
  7. w: (762280 % 79)=9 j: 1 -- j1: 3
  8. w: (2106 % 79)=52 j: 2 -- j2: 1
  9. w: (445387 % 79)=64 j: 2 -- j2: 0
  10. w: (721540 % 25)=15 j: 1 -- j1: 2
  11. w: (228762 % 25)=12 j: 1 -- j1: 1
  12. w: (945271 % 25)=21 j: 1 -- j1: 0

## 2. Now run with two specific jobs: each of length 10, but one (job 0) with just 1 ticket and the other (job 1) with 100 (e.g., -l 10:1,10:100). What happens when the number of tickets is so imbalanced? Will job 0 ever run before job 1 completes? How often? In general, what does such a ticket imbalance do to the behavior of lottery scheduling?

This causes that job 0 will be almost always be ran after job 1 since almost all of the tickets belong to job 1, thus it has the most chance to be selected.

## 3. When running with two jobs of length 100 and equal ticket allocations of 100 (-l 100:100,100:100), how unfair is the scheduler? Run with some different random seeds to determine the (probabilistic) answer; let unfairness be determined by how much earlier one job finishes than the other.

## 4. How does your answer to the previous question change as the quantum size (-q) gets larger?

## 5. Can you make a version of the graph that is found in the chapter? What else would be worth exploring? How would the graph look with a stride scheduler?
