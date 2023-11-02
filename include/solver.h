#include <stdio.h>
#include <stdlib.h>
#include "stl.h"

int bfs(int** graph, int vertices, int startVertex);

int* min_arbrorescence(int** graph, int vertices, int root);

int* create_f_star(int** graph, int vertices, int root);

int check_cycle(int vertices, int root, int* chosenEdges);
int* find_cycle(int vertices, int cycleStart, int* chosenEdges);

int** compress_graph(int** graph, int vertices, int root, int* minEdges, int* inCycle, int cycleSize, int cycleBeing, int* newRoot, int* mapG2GDash, int* mapGDash2G);
int* decompress_arborescence(int** graph, int vertices, int verticesDash, int* f_star, int* inCycle, int* arbroDash, int* GDash2G);