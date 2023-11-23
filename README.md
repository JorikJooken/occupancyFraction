# Occupancy fraction
This repository contains code and data related to the occupancy fraction of a graph (see the paper "S. Cambie and J. Jooken, Counterexamples to conjectures on the occupancy fraction of graphs, manuscript, 2023" available at https://arxiv.org/pdf/2311.05542.pdf for more details). We used this to disprove Conjectures 2, 3, 4 and 5 from the paper "G. Perarnau and W. Perkins. Counting independent sets in cubic graphs of given girth. J. Combin. Theory Ser. B, 133:211–242, 2018." and the conjecture from "J. Cutler and A. J. Radcliffe. Minimizing the number of independent sets in triangle-free regular
graphs. Discrete Math., 341(3):793–800, 2018."

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
./genregFolder/genreg 20 3 4 -g stdout | ./minimumOccupancyFractionExecutable
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

### countHomomorphisms.cpp
The program can be compiled by the following command:
```bash
g++ -g -std=c++11 -O3 countHomomorphisms.cpp -o countHomomorphismsExecutable
```

This program expects pairs of graphs (H,G) as input (one graph on each line in graph 6 format). The program will compute hom(G,H): the number of homomorphisms from G to H (as well as the normalized number of homomorphisms obtained by taking the |V(G)|-th root). It will also output for each H which graph G had the highest normalized number of homomorphisms.

Invoking the command

```bash
./countHomomorphismsExecutable < connectedCounterexampleGalvinGraphs1.g6
```

will produce the output:

```bash
nbHom: 24
normalizedNbHom: 1.48774
nbHom: 42
normalizedNbHom: 1.86441
Bw
Best: ElUg
Corresponding: 1.86441
```

This indicates that hom(G,K_3)=24 and hom(K_{3,3},K_3)=42 (where G is the K_4^{-}-chain as defined in the paper).

### countHomomorphismsLooped.cpp
The program can be compiled by the following command:
```bash
g++ -g -std=c++11 -O3 countHomomorphismsLooped.cpp -o countHomomorphismsLoopedExecutable
```

This program works similarly as 'countHomomorphisms', but instead it will add a loop to each vertex of H and count the number of homomorphisms from G to H_looped.

Invoking the command

```bash
./countHomomorphismsLoopedExecutable < connectedCounterexampleGalvinGraphs2.g6
```

will produce the output:

```bash
nbHom: 58374
normalizedNbHom: 3.94255
nbHom: 3732
normalizedNbHom: 3.93843
EfPw
Best: G}GOW[
Corresponding: 3.94255
```

This indicates that hom(G,H_0)=58734 and hom(K_{3,3},H_0)=3732.

### *.mw

There are 5 Maple files ("CR_conj.mw", "PPconj2.mw", "PPconj3.mw", "PPconj4.mw" and "PPconj5.mw"). Each of these files is self-contained and contains a description of what it does. We also provide PDF versions so that the content of the file can also be read in case you do not have Maple available.
 
## DATA
### counterExamplesToConjectures.txt

This file contains on overview of the counterexamples that we found to Conjectures 2, 3, 4 and 5 from the paper "G. Perarnau and W. Perkins. Counting independent sets in cubic graphs of given girth. J. Combin. Theory Ser. B, 133:211–242, 2018." and the conjecture from "J. Cutler and A. J. Radcliffe. Minimizing the number of independent sets in triangle-free regular
graphs. Discrete Math., 341(3):793–800, 2018."
