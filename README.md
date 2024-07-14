# SudokuSolvers
C++ Refresher Comparing Various Sudoku Solver Algos

## Sudoku Algorithms

There are 6 algorithms that are investigated (not really, just 5).

- Brute Force V1
- Brute Force V2
- Brute Force V3
- Backtrack V1
- Backtrack V2
- Backtrack V3


### Brute Force V1
This brute force algortihm doesn't care much about the rules about the possibilities. It simply locates all the empty cells and chages one at a time going through all the options until it finds the solution. Say there are 3 open cells. It means to may take up to 9*9*9=729 attempts at finding the right solution. This quickly scales up if you have 40 empty cells for example. As such it makes no sense to event implement this, because it is only testable on suokus that pose no real difficulty to solving. 

### Brute Force V2
This version improves on V1, by taking stock of the existing values. That means the algortihm first calculates all possible values for each cell, such that the brute force algorithm won't try completely impossible numbers (yeah yeah, no such thing as slightly impossible or completely impossible, but you know what I mean). It then only tries the subset solutions within the superset of all random numbers. It is a little faster but not much. It updates all the numbers every time...

### Brute Force V3
That's where V3 comes in - rather than updating the whole grid every single time, we track which cell should be updated next, so we fill in just one cell every time, rather than going through all 81 one of them. Roughly 81x speedup you'd expect... but its more like 1.2x speedup. Overheads, overheads, overheads...

### Backtrack V1
Simple way to improve over brute force is to check for every new filled in cell whether the value inserted is still legal. If it is legal we simply fill in the cell and move on the next. If we arrive at a cell where there are no possible values, we know we made a mistake somewhere before, so we move back one cell and try the next value following the same rule as above. This prevents us from checking some stupid solutions which for example consist of rows of 1 or something similar. While in theory it is a much better algorithm it is still the same time complexity as Brute Force 9<sup>N*N</sup>, where N is the grid size (9).

### Backtrack V2
So far we haven't considered any traditional sudoku solving cleverness, i.e. if a cell has only one possible candidate it's a no brainer to insert it and recheck neighbouring cells to see if anything else had fallen into place too. We then iterate over the grid like that until there is a deadlock or the solution has been found. If deadlock occurs we simply finish it off with some backtracking V1.

### Backtrack V3
This is the same as V1 but we implement it the Computerphile way - recursion. This may generate a mahoosive stack, but at its core it should work exactly the same.

## Testing

I have downloaded (https://www.printable-sudoku-puzzles.com/wfiles/) lots (30K) sudokus of various complexitites. I then replicated them 3 times, so each sudoku is solved 3 times for each algortihm (no real point testing any of the Brute Force algos on such a vast dataset. It would take more time than there has ever been since the Big Bang). We then take a mean of each solve and plot a histogram and print out key stats. There are dispalyed in the jupyter notebook attached to this repo.

So the results are not something super wild and crazy. Overall the trend can be summarised as t(V3) > t(V1) > t(V2), where t(x) is the execution time of algo x. So V2 wins right? Well, sort of. While it does have the highest chance of being the quickest for any given sudoku, it doesn't produce the fastest times in those edge cases - because of.... OVERHEADS! In those edge cases of sudoku being super simple recursion wins as it has far fewer overheads. You may argue that I could rewrite V1 and V2 with fewer overheads and you would be right. But I didn't so recursion wins the ultimate fastest solve time.


Times presented in milliseconds.
| **Algortihm** | **Recursion** | **Backtrack V1** | **Backtrack V2** |
|---------------|---------------|------------------|------------------|
|     **count** |  30000.000000 |     30000.000000 |     30000.000000 |
|      **mean** |      1.292872 |         1.120853 |         0.525756 |
|       **std** |      6.107498 |         4.941479 |         1.933150 |
|       **min** |      0.005625 |         0.060486 |         0.069306 |
|       **25%** |      0.016334 |         0.074569 |         0.153903 |
|       **50%** |      0.106236 |         0.154840 |         0.211757 |
|       **75%** |      0.606455 |         0.568917 |         0.345347 |
|       **max** |    292.102667 |       206.090333 |       147.256333 |

P.S. I run this with -03 optimisation flag set and with -funroll-loops flag too to squeeze the most out of this M2 chipset on my MacBook Air.