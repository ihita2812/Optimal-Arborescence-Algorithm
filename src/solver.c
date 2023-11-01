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

        //inCycle[i] = 1 if i is in cycle, else 0
        int* inCycle = (int*)malloc(vertices * sizeof(int));
        for (int i=0; i<vertices; i++) {
            inCycle[i] = 0;
        }
        for (int i=0; i<cycleSize; i++) {
            inCycle[cycle[i]] = 1;
        }

        //making compressed graph
        int rootDash;
        int verticesDash = vertices - cycleSize + 1;
        int* map2New;
        int* mapFromNew;
        map2New = (int*)malloc(vertices * sizeof(int));
        mapFromNew = (int*)malloc(verticesDash * sizeof(int));    
        int** graphDash = compress_graph(graph, vertices, root, f_star, inCycle, cycleSize, cycleExists-1, &rootDash, map2New ,mapFromNew);

        //--------debugging-------------------------------------------------
        printf("This is the map:\n");
        for (int i=0; i<vertices; i++) {
            printf("%d : %d\n", i+1, map2New[i]+1);
        }
        printf("-------------------------------------------------\n");
        printf("This is the reverse map:\n");
        for (int i=0; i<verticesDash; i++) {
            printf("%d : %d\n", i+1, mapFromNew[i]+1);
        }
        printf("-------------------------------------------------\n");
        printf("This is new graph:\n");
        for (int i=0; i<verticesDash; i++) {
            for (int j=0; j<verticesDash; j++) {
                if (graphDash[i][j] != -1) {
                    printf("%d %d %d\n", i+1, j+1, graphDash[i][j]);
                }
            }
        }
        //--------debugging-------------------------------------------------

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
//if cycle doesn't exist, returns 0
//if cycle exists, returns starting node of cycle
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
            realloc(foundCycle, (i+1)*sizeof(int));
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

// compress_graph(graph, vertices, root, f_star, inCycle, cycleSize, cycleExists-1, map2New ,mapFromNew)
int** compress_graph(int** graph, int vertices, int root, int* minEdges, int* inCycle, int cycleSize, int cycleBegin, int* newRoot, int* mapG2GDash, int* mapGDash2G) {
    int** newGraph;

    //decalring the compressed graph
    int newVertices = vertices - cycleSize + 1;
    newGraph = (int**)malloc(newVertices * sizeof(int*));
    for (int i=0; i<newVertices; i++) {
        newGraph[i] = (int*)malloc(newVertices*sizeof(int));
    }
    for (int u=0; u<newVertices; u++) {
        for (int v=0; v<newVertices; v++) {
            newGraph[u][v] = -1;
        }
    }

    //create maps for which node in graph maps to which node in compressed graph
    int curr = 0;
    for (int i=0; i<vertices; i++) {
        if (inCycle[i] == 1) {
            mapG2GDash[i] = newVertices-1;
            mapGDash2G[newVertices-1] = cycleBegin;
        }
        else {
            mapG2GDash[i] = curr;
            mapGDash2G[curr] = i;
            curr++;
        }
    }
    *newRoot = mapG2GDash[root-1] + 1;

    //edge weights for new graph
    for (int u=0; u<vertices; u++) {
        for (int v=0; v<vertices; v++) {
            if (v != (root-1)) { 
                int uInCycle = inCycle[u];
                int vInCycle = inCycle[v];
                int minEdgeWeight = graph[minEdges[v]][v];
                
                if (!uInCycle && !vInCycle) { //external edge
                    if (graph[u][v] != -1) newGraph[mapG2GDash[u]][mapG2GDash[v]] = (graph[u][v] - minEdgeWeight);
                }
                
                else if (uInCycle && vInCycle) { //internal edge
                    //do not add edge
                }
                
                else { //outgoing or incoming edge
                    if (graph[u][v] == -1) {
                        //don't do anything
                    }
                    else {
                        if (newGraph[mapG2GDash[u]][mapG2GDash[v]] == -1) {
                            newGraph[mapG2GDash[u]][mapG2GDash[v]] = (graph[u][v] - minEdgeWeight);
                        } else {
                            if ((graph[u][v] - minEdgeWeight) < newGraph[mapG2GDash[u]][mapG2GDash[v]]) {
                                newGraph[mapG2GDash[u]][mapG2GDash[v]] = (graph[u][v] - minEdgeWeight);
                            }
                        }
                    }
                }
            }
        }
    }

    return newGraph;
}

