# Homework (Simulation)
In this homework, you will use a simple program, which is known as paging-linear-translate.py, to see if you understand how simple virtual-to-physical address translation works with linear page tables. See the README for details.
# Questions
1. Before doing any translations, let’s use the simulator to study how linear page tables change size given different parameters. Compute the size of linear page tables as different parameters change. Some suggested inputs are below; by using the -v flag, you can see how many page-table entries are filled. First, to understand how linear page table size changes as the address space grows, run with these flags:
    -P 1k -a 1m -p 512m -v -n 0
    -P 1k -a 2m -p 512m -v -n 0
    -P 1k -a 4m -p 512m -v -n 0
Then, to understand how linear page table size changes as page size grows:
    -P 1k -a 1m -p 512m -v -n 0
    -P 2k -a 1m -p 512m -v -n 0
    -P 4k -a 1m -p 512m -v -n 0
Before running any of these, try to think about the expected trends. How should page-table size change as the address space grows? As the page size grows? Why not use big pages in general?

    Generally as the address space(`-a`) grows and page size (`-P`) stays the same we can observe the page table size changes as a multiply of the adress space. For example when the -P is 1k and -a is 4, then we need 4 table to represent 1 adress space.
    The opposite is true when the page size increases as we can fit more adress spaces in the same page.

    The conclusion is to not set the page size too low, because then the overhead of translating of address spaces becomse too high, but also not set it too high either, because then we could end up using more space if we can't will all of the pages.

2. Now let’s do some translations. Start with some small examples, and change the number of pages that are allocated to the address space with the -u flag. For example:
    -P 1k -a 16k -p 32k -v -u 0
    -P 1k -a 16k -p 32k -v -u 25
    -P 1k -a 16k -p 32k -v -u 50
    -P 1k -a 16k -p 32k -v -u 75
    -P 1k -a 16k -p 32k -v -u 100
What happens as you increase the percentage of pages that are al- located in each address space?
