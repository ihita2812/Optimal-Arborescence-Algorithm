#include <stdio.h>
#include <stdlib.h>
#include "../include/stl.h"

int* min_arbrorescence(int** graph, int vertices, int root);

int* create_f_star(int** graph, int vertices, int root);

int check_cycle(int vertices, int root, int* chosenEdges);
int* find_cycle(int vertices, int cycleStart, int* chosenEdges);

int** compress_graph(int** graph, int vertices, int root, int* minEdges, int* cycle, int cycleSize);

int* decompress_arborescence(int** graph, int vertices, int edges, int root);