//file for implementing input and output

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
    printf("\n-------------------------------------------------------\n");
    printf("\n        Methods to execute program:\n");
    printf("(1) algo help\n");
    printf("                      or\n");
    printf("(2) algo <testFile.txt>\n");
    printf("                      or\n");
    printf("(3) algo <number of vertices> <number of edges> <root node>\n\n");
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

                graph = (int**)malloc(M * sizeof(int*));
                for (int edge = 0; edge < M; edge++) 
                    graph[edge] = (int*)malloc(3 * sizeof(int));
                
                for (int edge = 0; edge < M; edge++) {
                    if (fscanf(fp, "%d %d %d", &graph[edge][0], &graph[edge][1], &graph[edge][2]) == 0) {
                        printf("ERROR IN FILE FORMATTING.\nSee help-\n");
                        help();
                        exit(1);
                    }
                    if (graph[edge][0] > N || graph[edge][0] < 0 || graph[edge][1] > N || graph[edge][1] < 0) {
                        printf("INCORRECT VALUE OF <starting node> OR <ending node>!\nSee help-\n");
                        help();
                        exit(1);
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

        graph = (int**)malloc(M * sizeof(int*));
        for (int edge = 0; edge < M; edge++) 
            graph[edge] = (int*)malloc(3 * sizeof(int));
        
        printf("\nInput values for each edge in format\n");
        printf("<starting node> <ending node> <weight of edge>:\n");
        for (int edge = 0; edge < M; edge++) {
            printf("For edge %d: ", edge+1);
            if (scanf("%d %d %d", &graph[edge][0], &graph[edge][1], &graph[edge][2]) < 0) {
                printf("ERROR IN INPUTTING DATA!\nSee help-\n");
                help();
                exit(1);
            }
            if (graph[edge][0] > N || graph[edge][0] < 0 || graph[edge][1] > N || graph[edge][1] < 0) {
                printf("INCORRECT VALUE OF <starting node> OR <ending node>!\nSee help-\n");
                help();
                exit(1);
            }
        }
    }

    else { //wrong arguments
        printf("TOO MANY ARGUMENTS!\nSee help-\n");
        help();
        exit(1);
    }
}