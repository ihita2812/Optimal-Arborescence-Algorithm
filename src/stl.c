#include "stl.h"

//QUEUE

void kyu_init(kyu* q) {
    q->size = 0;
    q->front = -1;
    q->rear = -1;
}

void kyu_push(kyu* q, int item) {
    q->size++;
    if (q->size > MAX_VERTICES) {
        printf("Too many vertices!\nMaximum vertices allowed are %d\n.", MAX_VERTICES);
        exit(1);
    }
    q->items[(q->size)-1] = item;
    q->front = q->items[0];
    q->rear = q->items[(q->size)-1];
}

int kyu_pop(kyu* q) {
    if (q->size == 0) {
        return (int)NULL;
    }
    int pop = q->front;
    for (int i=0; i<q->size-1; i++) {
        q->items[i] = q->items[i+1];
        q->items[i+1] = (int)NULL;
    }
    q->size--;
    q->front = q->items[0];
    q->rear = q->items[q->size-1];
    return pop;
}
