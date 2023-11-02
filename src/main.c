//file for implementing input and output

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solver.h"

void help() {
    printf("\n-------------------------------------------------------\n");
    printf("\n        Methods to execute program:\n");
    printf("(1) ./algo.exe help\n");
    printf("                      or\n");
    printf("(2) ./algo.exe <testFile.txt>\n");
    printf("                      or\n");
    printf("(3) ./algo.exe <number of vertices> <number of edges> <root node>\n\n");
    printf("\n        Details of each method:\n");
    printf("(1) Will print this help message.\n");
    printf("(2) Will start the program, guidelines for which are-\n");
    printf("          |- <testFile.txt> should be in the directory 'test'.\n");
    printf("          |- Vertex numbers are 1-indexed.\n");
    printf("          |- For guidelines on format of testFile, see README.\n");
    printf("(3) Will start the program, guidelines for which are-\n");
    printf("          |- Both <number of vertices> and <number of edges> should be positive integers.\n");
    printf("          |- <root node> value should be less than <number of vertices>.\n");
    printf("          |- Program will further ask for details of each directed edge in format <starting node> <ending node> <weight of edge>.\n");
    printf("             Values of <starting node> and <ending node> should be less than <root node>. \n");
    printf("             Values of <weight of edge> should be positive real numbers.\n\n");
    printf("          |- Vertex numbers are 1-indexed.\n");
    printf("PROGRAM WILL TERMINATE IF-\n");
    printf("ALL VERTICES ARE NOT REACHABLE FROM <root node>,\n");
    printf("                      or\n");
    printf("ANY OTHER SITUATION WHERE ARBRORESCENCE DOESN'T EXIST.\n");
    printf("\n-------------------------------------------------\n");
}

int main(int argc, char* argv[]) {
    int N, M, R;
    int** graph;

    if (argc < 2) { //wrong arguments
        printf("NOT ENOUGH ARGUMENTS!\nSee help-\n");
        help();
        exit(1);
    }

    else if (argc == 2) { //help or input via file
        if (!strcmp("help", argv[1])) {
            //help
            help();
            exit(0);
        }

        else {
            //input via file
            const char* fileName = argv[1];
            char fullFileName[100] = "../test/";
            strcat(fullFileName, fileName);
            FILE* fp = fopen(fullFileName, "r");
            if (fp == NULL) {
                //file not found
                printf("FILE NOT FOUND! MAKE SURE FILE IS IN 'TEST' DIRECTORY.\nSee help-\n");
                help();
                exit(1);
            }
            
            else {
                if (fscanf(fp, "%d %d %d", &N, &M, &R) == 0) {
                    printf("ERROR IN FILE FORMATTING.\nSee help-\n");
                    help();
                    exit(1);
                }
            
                if (N<1 || M<0) {
                    printf("INVALID NUMBER OF VERTICES(%d) OR NUMBER OF EDGES(%d)!\nSee help-\n", N, M);
                    help();
                    exit(1);
                }

                if (R>N || R<1) {
                    printf("INVALID VALUE OF ROOT NODE(%d)!\nSee help-\n", R);
                    help();
                    exit(1);
                }

                graph = (int**)malloc(N * sizeof(int*));
                for (int i=0; i<N; i++)
                    graph[i] = (int*)malloc(N * sizeof(int));
            
                for (int i=0; i<N; i++) {
                    for (int j=0; j<N; j++) {
                        graph[i][j] = -1;
                    }
                }

                for (int edge = 0; edge < M; edge++) {
                    int start, end, weight;
                    if (fscanf(fp, "%d %d %d", &start, &end, &weight) == 0) {
                        printf("ERROR IN FILE FORMATTING.\nSee help-\n");
                        help();
                        exit(1);
                    }
                    if (start > N || start < 1 || end > N || end < 1) {
                        printf("INVALID VALUE OF <starting node> OR <ending node>!\nSee help-\n");
                        help();
                        exit(1);
                    }
                    if (weight < 0) {
                        printf("WEIGHT VALUE SHOULD BE >= 0!\nSee help-\n");
                        help();
                        exit(1);
                    }

                    if (start == end || end == R) {
                        //do nothing
                    } else {
                        if (graph[start-1][end-1] == -1) {
                            graph[start-1][end-1] = weight;
                        } else {
                            if (weight < graph[start-1][end-1])
                                graph[start-1][end-1] = weight;
                        }
                    }
                }

            }
        }

    }

    else if (argc == 4) { //input via command line
        N = atoi(argv[1]);
        M = atoi(argv[2]);
        R = atoi(argv[3]);

        if (N<1 || M<0) {
            printf("INVALID NUMBER OF VERTICES(%d) OR NUMBER OF EDGES(%d)!\nSee help-\n", N, M);
            help();
            exit(1);
        }

        if (R>N || R<1) {
            printf("INVALID VALUE OF ROOT NODE(%d)!\nSee help-\n", R);
            help();
            exit(1);
        }

        graph = (int**)malloc(N * sizeof(int*));
        for (int i=0; i<N; i++)
            graph[i] = (int*)malloc(N * sizeof(int));
    
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                graph[i][j] = -1;
            }
        }

        for (int edge = 0; edge < M; edge++) {
            printf("For edge %d: ", edge+1);
            int start, end, weight;
            if (scanf("%d %d %d", &start, &end, &weight) < 0) {
                printf("ERROR IN INPUTTING DATA!\nSee help-\n");
                help();
                exit(1);
            }
            if (start > N || start < 1 || end > N || end < 1) {
                printf("INCORRECT VALUE OF <starting node> OR <ending node>!\nSee help-\n");
                help();
                exit(1);
            }
            if (weight < 0) {
                printf("WEIGHT VALUE SHOULD BE >= 0!\nSee help-\n");
                help();
                exit(1);
            }

            if (start == end || end == R) {
                //do nothing
            } else {
                if (graph[start-1][end-1] == -1) {
                    graph[start-1][end-1] = weight;
                } else {
                    if (weight < graph[start-1][end-1])
                        graph[start-1][end-1] = weight;
                }
            }
        }

    }

    else { //wrong arguments
        printf("INVALID NUMBER OF ARGUMENTS!\nSee help-\n");
        help();
        exit(1);
    }

    int connected = bfs(graph, N, R);
    if (connected == 0) {
        printf("Graph entered is not connected!\n");
        exit(1);
    } else if (connected == -1) {
        printf("ERROR IN BFS!\n");
        exit(1);
    } else {
        //
    }

    int* min_arbro = min_arbrorescence(graph, N, R);
    int cost = 0;
    printf("Chosen edges in min arbrorescence are:\n");
    for (int i=0; i<N; i++) {
        if (min_arbro[i] == -1) {
            //
        }
        else {
            printf("%d -> %d\n", min_arbro[i]+1, i+1);
            cost+= graph[min_arbro[i]][i];
        }
    }
    printf("Cost of min arbrorescence: %d\n", cost);

    return 0;   

}