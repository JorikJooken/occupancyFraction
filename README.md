# Occupancy fraction
This repository contains code and data related to the occupancy fraction of a graph.

Below, we briefly describe the different programs. We will assume that Linux is being used and that GENREG is installed. The details on how to install GENREG can be found on [this link](https://www.mathe2.uni-bayreuth.de/markus/reggraphs.html). The graphs that we are dealing with will be in graph6 format.


## CODE
### minimumOccupancyFraction.cpp
The program can be compiled by the following command:
```bash
g++ -g -std=c++11 -O3 minimumOccupancyFraction.cpp -o minimumOccupancyFractionExecutable
```

The program expects as input a list of graphs (in graph6 format, one per line) which all have the same order. The program will output the graphs together with their independence polynomials that do not majorize another independence polynomial from the input (i.e. these graphs are candidates to have minimum occupancy fraction for some lambda).

Invoking the command

```bash
./genreg/genreg-incl-bip-march-native-fastest/genreg-incl-bip-march-native-fastest/genreg 20 3 4 -g stdout | ./minimumOccupancyFractionExecutable
```

will result in the following output:
```
SsP@PGWD_A?C?A?A??_?G??g?AO?BG?Ao
21
1 20 160 660 1510 1908 1232 332 25 0 0 0 0 0 0 0 0 0 0 0 0 
SsP@P?SCOO?`?_?O_C??`?A_?C_?A_??[
21
1 20 160 660 1510 1912 1240 320 5 0 0 0 0 0 0 0 0 0 0 0 0
```

This means that there are 2 3-regular graphs on 20 vertices with girth at least 4 for which the independence polynomial does not majorize another independence polynomial.

### calcAlphaAndMaximize.cpp
The program can be compiled by the following command:
```bash
g++ -g -std=c++11 -O3 calcAlphaAndMaximize.cpp -o calcAlphaAndMaximizeExecutable
```

The program expects as input a list of graphs (in graph6 format). The program will compute the occupancy fraction alpha(lambda) for these graphs for lambda=0.1, 0.2, ..., 100.0 and it will output for each lambda which graph has the largest occupancy fraction.

Invoking the command

```bash
./calcAlphaAndMaximizeExecutable < cage4RegularGirth6And32VertexMaximizer.g6
```

Will produce for each lambda the graph for which alpha(lambda) is maximal together with the value of alpha(lambda).

## DATA
### counterExamplesToConjectures.txt

This file contains on overview of the counterexamples that we found to Conjectures 2, 3, 4 and 5 from the paper "G. Perarnau and W. Perkins. Counting independent sets in cubic graphs of given girth. J. Combin. Theory Ser. B, 133:211–242, 2018."
