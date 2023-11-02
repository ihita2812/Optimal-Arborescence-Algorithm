#ifndef STL_H_
#define STL_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 500

//QUEUE

typedef struct kyu {
    int items[MAX_VERTICES];
    int size;
    int front;
    int rear;
} kyu;

void kyu_init(kyu*);
void kyu_push(kyu*, int);
int kyu_pop(kyu*);

#endif