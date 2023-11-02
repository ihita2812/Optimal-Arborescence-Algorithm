# Optimal-Arborescence-Algorithm
Finding optimal aborescence for a directed graph using Chu-Liu-Edmond's algorithm.<br>
This is a project for undergraduate course **CS302- Analysis and Design of Algorithms**, under Dr. Apurva Mudgal at IIT Ropar.

## Constraints on graph:
1. The maximum number of vertices allowed in the graph is 500.
2. Graph should be connected.
3. The vertex numbers are indexed from 1.
4. The edge weights should be non negative integers.<br>
If any of the above constraints are not met, program will exit.

## How to buid:
```console
$ cd src
$ make
```

## How to run:
```console
$ cd ../bin
$ ./algo.exe <arguments>
```
There are 3 ways of running the program:

### Asking for help
```console
$ ./algo.exe help
```
Will display a short help message on how to run the program

### Entering arguments through a file
`$ ./algo.exe <name of test file>`<br>
- Test file should be in directory [test](test/).
- Format of test file:
    - First line should be 3 space seperated integers:<br>
        `<number of vertices(N)> <number of edges(M)> <root node(R)>`
    - Then should follow M lines, describing M edges, each containing 3 space seperated integers:<br>
        `<starting node> <ending node> <weight of edge`

### Entering arguments through command line
`$ ./algo.exe <N> <M> <R>`<br>
- Here, N is the number of vertices, M is the number of edges and R is the root node.
- Program will then prompt you to enter details of M edges in the same format as for input file.

## How to clean:
```console
$ cd ../src
$ make clean
```

## Contact for issues:
sinhaihita@gmail.com

## Creators:
Ihita Sinha<br>
Rhitvik Anand<br>
Anshika<br>
Mohit Bhuria<br>
Shashank Kumar<br>