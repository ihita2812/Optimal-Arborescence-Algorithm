#include "solver.h"

//bfs to check connectedness of graph
int bfs(int** graph, int vertices, int startVertex) {
  kyu q;
  kyu_init(&q);
  
  int* visited = (int*)malloc(vertices * sizeof(int));
  for (int i=0; i<vertices; i++) {
    visited[i] = 0;
  }

  int numVisited = 0;

  visited[startVertex-1] = 1;
  numVisited++;
  kyu_push(&q, startVertex-1);
  
  while (q.size != 0) {
    int currentVertex = kyu_pop(&q);
    
    for (int i=0; i<vertices; i++) {
        if (graph[currentVertex][i] != -1) {
            if (visited[i] == 0) {
                visited[i] = 1;
                numVisited++;
                kyu_push(&q, i);
            }
        }
    }
  }

  if (numVisited == vertices) return 1;
  else if (numVisited < vertices) return 0;
  else return -1;
}

//returns array of edges in the min arbroscence
//if (u,v) is a selected edge, then min_arbro_array[v] = u
int* min_arbrorescence(int** graph, int vertices, int root) {

    int* min_arbro_array;

    int* f_star = create_f_star(graph, vertices, root);

    int cycleExists = check_cycle(vertices, root, f_star);
    if (cycleExists == 0)
        min_arbro_array = f_star;
    else {
        int* cycle = find_cycle(vertices, cycleExists-1, f_star);
        
        int cycleSize = 0;
        for (int i=1; i<vertices; i++) {
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
        int** graphDash = compress_graph(graph, vertices, root, f_star, inCycle, cycleSize, cycleExists-1, &rootDash, map2New, mapFromNew);

        int* min_arbro_array_Dash = min_arbrorescence(graphDash, verticesDash, rootDash);

        min_arbro_array = decompress_arborescence(graph, vertices, verticesDash, f_star, inCycle, min_arbro_array_Dash, mapFromNew);

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

//function to compress cycle into single node and return new graph
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

//function to translate arbrorescence in compressed graph to real arbrorescence
int* decompress_arborescence(int** graph, int vertices, int verticesDash, int* f_star, int* inCycle, int* arbroDash, int* GDash2G) {
    int* arbro = (int*)malloc(vertices * sizeof(int));

    for (int i=0; i<vertices; i++) {
        arbro[i] = -1;
    }

    for (int i=0; i<verticesDash; i++) {
        if (arbroDash[i] == -1) {
            //do nothing
        }
        else {
            if (inCycle[GDash2G[i]] == 0 && inCycle[GDash2G[arbroDash[i]]] == 0) {
                arbro[GDash2G[i]] = GDash2G[arbroDash[i]];
            }
            else if (inCycle[GDash2G[i]] == 1) {
                int connecterToTree = GDash2G[arbroDash[i]];
                int bestWeight = 1e8;
                int currentNode = GDash2G[i];
                int bestNode = currentNode;

                int itr = 0;
                while (1) {
                    if (currentNode == GDash2G[i] && itr > 0) break;
                    if (graph[connecterToTree][currentNode] == -1) {
                        //doesnt have a connection
                    }
                    else {
                        if (graph[connecterToTree][currentNode] < bestWeight) {
                            bestWeight = graph[connecterToTree][currentNode];
                            bestNode = currentNode;
                        }
                    }
                    currentNode = f_star[currentNode];
                    itr++;
                }

                if (bestNode == -1) {
                    printf("ERROR IN DECOMPRESSING!\n");
                    exit(0);
                }

                arbro[bestNode] = connecterToTree;
            }
        }
    }

    for (int i=0; i<vertices; i++) {
        if (arbro[i] == -1) {
            arbro[i] = f_star[i];
        }
    }

    return arbro;
}
