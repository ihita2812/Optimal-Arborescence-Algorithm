#include <stdio.h>
#include <stdlib.h>

int* create_f_star(int** graph, int vertices, int edges, int root);

int check_cycle(int** graph, int vertices, int edges, int root);

void compress_graph(int** graph, int vertices, int edges, int root);

void decompress_arborescence(int** graph, int vertices, int edges, int root);