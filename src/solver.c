#include "../include/solver.h"

int* min_arbrorescence(int** graph, int vertices, int root) {

    //--------debugging-------------------------------------------------
    // for (int i=0; i<vertices; i++) {
    //     for (int j=0; j<vertices; j++) {
    //         // if (graph[i][j] != -1) {
    //             printf("%d %d %d\n", i+1, j+1, graph[i][j]);
    //         // }
    //     }
    // }
    //--------debugging--------------------------------------------------

    int* min_arbro_array;

    int* f_star = create_f_star(graph, vertices, root);

    //--------debugging-------------------------------------------------
    // for (int i=0; i<vertices; i++) {
    //     printf("%d %d\n", i+1, f_star[i]+1);
    // }
    //--------debugging-------------------------------------------------

    int cycleExists = check_cycle(vertices, root, f_star);
    if (cycleExists == 0)
        min_arbro_array = f_star;
    else {
        int* cycle = find_cycle(vertices, cycleExists-1, f_star);
        
        int cycleSize = 0;
        // printf("%d ", cycle[0]+1);
        for (int i=1; i<vertices; i++) {
            // printf("%d ", cycle[i]+1);
            if (cycle[i] == cycle[0]) {
                cycleSize = i;
                break;
            }
        }

        int verticesDash = vertices - cycleSize + 1;

        // int** graphDash = compress_graph(graph, vertices, root, f_star, cycle, cycleSize);

    }

    return min_arbro_array;
}

//creates array f_star which stores source of min edge for every node
//if (u,v) is min edge for v, f_star[v] = u
int* create_f_star(int** graph, int vertices, int root) {
    int* f_star;

    f_star = (int*)malloc(vertices * sizeof(int));
    for (int i=0; i<vertices; i++)
        f_star[i] = -1;
    
    for (int v=0; v<vertices; v++) {
        if (v == (root-1)) {} //no need to do computation for root
        else {
            for (int u=0; u<vertices; u++) {
                if (graph[u][v] != -1) { //(u,v) exists
                    if (f_star[v] == -1) {
                        f_star[v] = u;
                    } else {
                        if (graph[u][v] <= graph[f_star[v]][v]) {f_star[v] = u;}
                        else {}
                    }
                }
            }
        }
    }

    return f_star;
}

//checks if a cycle exists in the edges chosen
int check_cycle(int vertices, int root, int* chosenEdges) {
    int cycleFound= 0;
    
    for (int v=0; v<vertices; v++) {
        if (v == root-1) {} //root cannot be in a cycle

        else {
            int current = v;
            while (cycleFound == 0) {
                if (chosenEdges[current] == -1) { //reached root, no cycle
                    break;
                }
                else if (chosenEdges[current] == v) { //reached v again, cycle exists
                    cycleFound = v+1;
                }
                else {
                    current = chosenEdges[current];
                }
            }
        }
    }

    return cycleFound;
}

//if cycle exists, finds that cycle
int* find_cycle(int vertices, int cycleStart, int* chosenEdges) {
    int* foundCycle = (int*)malloc(vertices*sizeof(int));

    int found = 0; int i = 0;
    int current = cycleStart;
    foundCycle[i] = current;
    i++;
    while (found == 0) {
        if (chosenEdges[current] == -1) { //reached root, no cycle
            printf("ERROR IN check_cycle\n");
            break;
        }
        else if (chosenEdges[current] == cycleStart) { //reached v again, cycle exists
            foundCycle[i] = cycleStart;
            realloc(foundCycle, i*sizeof(int));
            found = 1;
        }
        else {
            current = chosenEdges[current];
            foundCycle[i] = current;
            i++;
        }
    }

    return foundCycle;
}

/*
int** compress_graph(int** graph, int vertices, int root, int* minEdges, int* cycle, int cycleSize) {
    int** newGraph;

    int newVertices = vertices - cycleSize + 1;
    newGraph = (int**)malloc(newVertices * sizeof(int*));
    for (int i=0; i<newVertices; i++) {
        newGraph[i] = (int*)malloc(newVertices*sizeof(int));
    }

    int* map = (int*)malloc(vertices * sizeof(int));
    for (int i=0; i<vertices; i++) {
        //if i in cycle, map[i] = newVertices-1
        //else ?
            //if i<newVertices-1, map[i] = i
            //else?
    }



    return newGraph;
}
*/
